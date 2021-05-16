#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

bool MenuButtons::was_focused = false;
bool MenuButtons::was_loaded = false;
bool MenuButtons::is_full_screen = false;
float MenuButtons::music_audio_level = -12.5;
float MenuButtons::effect_audio_level = 6;

AudioStreamPlayer2D* MenuButtons::audio = nullptr;

MenuButtons::MenuButtons()
{
	was_focused = false;
	delta_time = 1.0 / 50;
}

MenuButtons::~MenuButtons() {}

void godot::MenuButtons::_init() {}

void godot::MenuButtons::_ready()
{
	//load scenes
	ResourceLoader* rld = ResourceLoader::get_singleton();
	menu_scene = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	option_scene = rld->load("res://Assets/Prefabs/Scenes/Option.tscn");
	notice_scene = rld->load("res://Assets/Prefabs/Scenes/Notice.tscn");
	game_scene = rld->load("res://main_scene.tscn");

	cast_to<Camera2D>(get_parent())->_set_current(true);

	// Set focus button in Menu and Notise scenes
	set_focus_mode(true);

	std::vector<String> name_buttons{ "Play", "Flower_button", "Back", "Resume" };

	if (find_parent("root") != nullptr && !find_parent("root")->has_node("MenuBackMusic"))
	{
		audio = cast_to<AudioStreamPlayer2D>(menu_back->instance());
		find_parent("root")->call_deferred("add_child", audio);
	}

	for (auto name : name_buttons)
	{
		if (find_node(name) != nullptr) 
		{
			cast_to<TextureButton>(find_node(name))->grab_focus();
			break;
		}
	}

	if (get_name() == "Option")
	{
		auto tmp_node = get_child(1)->get_child(0)->get_child(0);
		cast_to<Button>(tmp_node->get_child(0))->set_pressed(is_full_screen);
		cast_to<Slider>(tmp_node->get_child(2))->set_value(effect_audio_level);
		cast_to<Slider>(tmp_node->get_child(4))->set_value(music_audio_level);
	}

	if (get_name() == "Menu")
	{
		load_game();
		if (!was_loaded)
		{
			add_child(fade_in->instance());
			if (timer_music == nullptr)
			{
				timer_music = Timer::_new();
				add_child(timer_music);
			}
			timer_music->connect("timeout", this, "_fade_audio");
			timer_music->start(0.01);
			was_loaded = true;
		}
	}
}

void MenuButtons::_register_methods()
{
	register_method((char*)"_ready", &MenuButtons::_ready);
	register_method((char*)"_on_Play_pressed", &MenuButtons::_on_Play_pressed);
	register_method((char*)"_on_Option_pressed", &MenuButtons::_on_Option_pressed);
	register_method((char*)"_on_Quit_pressed", &MenuButtons::_on_Quit_pressed);
	register_method((char*)"_on_Back_pressed", &MenuButtons::_on_Back_pressed);
	register_method((char*)"_on_Flower_pressed", &MenuButtons::_on_Flower_pressed);
	register_method((char*)"_on_FullScreen_pressed", &MenuButtons::_on_FullScreen_pressed);
	register_method((char*)"_play_change_cursor_effect", &MenuButtons::_play_change_cursor_effect);
	register_method((char*)"_on_effects_value_changed", &MenuButtons::_on_effects_value_changed);
	register_method((char*)"_on_music_value_changed", &MenuButtons::_on_music_value_changed);
	register_method((char*)"_timeout", &MenuButtons::_timeout);
	register_method((char*)"_change_audio_volume", &MenuButtons::_change_audio_volume);
	register_method((char*)"_on_Resume_pressed", &MenuButtons::_on_Resume_pressed);
	register_method((char*)"_on_Menu_pressed", &MenuButtons::_on_Menu_pressed);
	register_method((char*)"_move_to_main_menu", &MenuButtons::_move_to_main_menu);
	register_method((char*)"_audio_fade_to_main_menu", &MenuButtons::_audio_fade_to_main_menu);
	register_method((char*)"_fade_audio", &MenuButtons::_fade_audio);
	
	register_property<MenuButtons, Ref<PackedScene>>("click_effect", &MenuButtons::click_effect, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("menu back music", &MenuButtons::menu_back, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("fade", &MenuButtons::fade, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("fade_in", &MenuButtons::fade_in, nullptr);
}

void godot::MenuButtons::_on_Resume_pressed(Input*)
{
	_play_effect();
	get_tree()->set_pause(false);
	cast_to<Camera2D>(get_node("/root/Node2D/Node/Camera2D"))->_set_current(true);
	get_parent()->queue_free();
}

void godot::MenuButtons::_on_Menu_pressed(Input*)
{
	_play_effect();
	if(get_name() == "Pause")
		was_loaded = false;

	add_child(fade->instance());

	if (timer_music_out == nullptr)
	{
		timer_music_out = Timer::_new();
		add_child(timer_music_out);
	}

	timer_music_out->connect("timeout", this, "_audio_fade_to_main_menu");
	timer_music_out->start(0.01);

	if (timer == nullptr)
	{
		timer = Timer::_new();
		add_child(timer);
	}

	timer->connect("timeout", this, "_move_to_main_menu");
	timer->start(1);
	Enemies::get_singleton()->_clear();
}

void godot::MenuButtons::_move_to_main_menu()
{
	get_tree()->set_pause(false);
	ResourceLoader* rld = ResourceLoader::get_singleton();
	menu_scene = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	get_node("/root")->add_child(menu_scene->instance());
	get_node("/root/Node2D")->queue_free();
	get_parent()->queue_free();
}

void godot::MenuButtons::save_game()
{
	auto save_game = File::_new();
	save_game->open("user://savegame_hunters.save", File::WRITE);

	Dictionary save_dict;
	save_dict = Dictionary::make("effect_level", effect_audio_level, "music_level", music_audio_level , "full_screen", is_full_screen);
	save_dict.to_json();

	save_game->store_line(save_dict.to_json());
	save_game->close();
}

void godot::MenuButtons::load_game()
{
	auto save_game = File::_new();
	if (!save_game->file_exists("user://savegame_hunters.save"))
		return; 

	save_game->open("user://savegame_hunters.save", File::READ);
	Dictionary node_data = JSON::get_singleton()->parse(save_game->get_line())->get_result();

	is_full_screen = node_data.values()[1];
	music_audio_level = node_data.values()[2];
	effect_audio_level = node_data.values()[0];

	OS::get_singleton()->set_window_fullscreen(is_full_screen);
	AudioServer::get_singleton()->set_bus_volume_db(1, effect_audio_level);
	if (!was_loaded)
	{
		AudioServer::get_singleton()->set_bus_volume_db(2, -80);
		AudioServer::get_singleton()->set_bus_volume_db(3, -80);
	}

	save_game->close();
}

void godot::MenuButtons::_timeout()
{
	timer->disconnect("timeout", this, "_timeout");
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://main_scene.tscn");

	find_parent("root")->add_child(res->instance());
	get_node("/root/MenuBackMusic")->queue_free();
	get_parent()->queue_free();
}

void godot::MenuButtons::_change_audio_volume()
{
	if (AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) <= -75)
	{
		return;
	}

	AudioServer::get_singleton()->set_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus()),
		AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) - 0.8);

	timer_music->disconnect("timeout", this, "_change_audio_volume");
	timer_music->connect("timeout", this, "_change_audio_volume");
	timer_music->start(delta_time);
}

void godot::MenuButtons::_on_Play_pressed(Variant)
{
	_play_effect();
	get_node("/root")->add_child(notice_scene->instance());
	get_parent()->queue_free();
}

void godot::MenuButtons::_on_Back_pressed(Variant)
{
	_play_effect();
	get_node("/root")->add_child(menu_scene->instance());
	get_parent()->queue_free();
}

void godot::MenuButtons::_on_Option_pressed(Variant)
{
	_play_effect();
	get_node("/root")->add_child(option_scene->instance());
	get_parent()->queue_free();
}

void godot::MenuButtons::_on_Quit_pressed(Variant)
{
	_play_effect();
	_exit_tree();
}

void godot::MenuButtons::_on_FullScreen_pressed(Variant)
{
	_play_effect();

	is_full_screen = !is_full_screen ? true : false;
	OS::get_singleton()->set_window_fullscreen(is_full_screen);

	save_game();
}

void godot::MenuButtons::_on_effects_value_changed(float value)
{
	if (value <= -34)
		value = -80;

	effect_audio_level = value;

	AudioServer::get_singleton()->set_bus_volume_db(1, value);

	save_game();
}

void godot::MenuButtons::_on_music_value_changed(float value)
{
	if (value <= -34)
		value = -80;

	music_audio_level = value;

	AudioServer::get_singleton()->set_bus_volume_db(2, value);

	save_game();
}

void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	_play_effect();
	add_child(fade->instance());

	if (timer == nullptr)
	{
		timer = Timer::_new();
		add_child(timer);
	}
	
	timer->connect("timeout", this, "_timeout");

	if (timer_music == nullptr)
	{
		timer_music = Timer::_new();
		add_child(timer_music);
	}

	timer_music->connect("timeout", this, "_change_audio_volume");

	delta_step = AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) / 50;

	timer_music->start(0.01);
	timer->start(1);
}

void godot::MenuButtons::_play_effect()
{
	get_node("/root")->add_child(click_effect->instance());
}

void godot::MenuButtons::_play_change_cursor_effect()
{
	if (was_focused)
	{
		get_parent()->add_child(click_effect->instance());
		return;
	}

	was_focused = true;
}

void godot::MenuButtons::_audio_fade_to_main_menu()
{
	timer_music_out->disconnect("timeout", this, "_audio_fade_to_main_menu");

	if (AudioServer::get_singleton()->get_bus_volume_db(2) <= -75
		&& AudioServer::get_singleton()->get_bus_volume_db(3) <= -75)
			return;

	if (AudioServer::get_singleton()->get_bus_volume_db(2) > -75)
		AudioServer::get_singleton()->set_bus_volume_db(2,
			AudioServer::get_singleton()->get_bus_volume_db(2) - 0.8);

	if (AudioServer::get_singleton()->get_bus_volume_db(3) > -75)
		AudioServer::get_singleton()->set_bus_volume_db(3,
			AudioServer::get_singleton()->get_bus_volume_db(3) - 0.8);

	timer_music_out->connect("timeout", this, "_audio_fade_to_main_menu");
	timer_music_out->start(0.01);
}

void godot::MenuButtons::_fade_audio()
{
	timer_music->disconnect("timeout", this, "_fade_audio");

	if (AudioServer::get_singleton()->get_bus_volume_db(2) >= music_audio_level
		&& AudioServer::get_singleton()->get_bus_volume_db(3) >= music_audio_level)
		return;

	AudioServer::get_singleton()->set_bus_volume_db(2,
		AudioServer::get_singleton()->get_bus_volume_db(2) + 0.8);

	AudioServer::get_singleton()->set_bus_volume_db(3,
		AudioServer::get_singleton()->get_bus_volume_db(3) + 0.8);

	timer_music->connect("timeout", this, "_fade_audio");
	timer_music->start(0.01);
}
