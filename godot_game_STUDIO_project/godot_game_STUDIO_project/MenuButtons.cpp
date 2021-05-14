#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

bool MenuButtons::was_focused = false;
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

	std::vector<String> name_buttons{ "Play", "Flower_button", "Back" };

	if (find_parent("root") != nullptr && !find_parent("root")->has_node("MenuBackMusic"))
	{
		audio = cast_to<AudioStreamPlayer2D>(menu_back->instance());
		find_parent("root")->call_deferred("add_child", audio);
		load_game();
	}

	// Set focus button 
	set_focus_mode(true);
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

	register_property<MenuButtons, Ref<PackedScene>>("click_effect", &MenuButtons::click_effect, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("menu back music", &MenuButtons::menu_back, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("fade", &MenuButtons::fade, nullptr);
}

void godot::MenuButtons::save_game()
{
	Godot::print("saving");
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
	AudioServer::get_singleton()->set_bus_volume_db(2, music_audio_level);

	save_game->close();
}

void godot::MenuButtons::_timeout()
{
	timer->disconnect("timeout", this, "_timeout");
	Godot::print("end");
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://main_scene.tscn");

	find_parent("root")->add_child(res->instance());
	get_node("/root/MenuBackMusic")->queue_free();
	get_parent()->queue_free();
}

void godot::MenuButtons::_change_audio_volume()
{
	AudioServer::get_singleton()->set_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus()),
		AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) + delta_step * 4);

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
	if (value <= -20)
		value = -80;

	effect_audio_level = value;

	AudioServer::get_singleton()->set_bus_volume_db(1, value);

	save_game();
}

void godot::MenuButtons::_on_music_value_changed(float value)
{
	if (value <= -20)
		value = -80;

	music_audio_level = value;

	AudioServer::get_singleton()->set_bus_volume_db(2, value);

	save_game();
}

void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	_play_effect();
	auto node = fade->instance();
	cast_to<Node2D>(node)->set_global_position(Vector2(640, 360));
	add_child(node);

	timer = Timer::_new();
	add_child(timer);
	timer->connect("timeout", this, "_timeout");

	timer_music = Timer::_new();
	add_child(timer_music);
	timer_music->connect("timeout", this, "_change_audio_volume");

	delta_step = AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) / 50;

	timer_music->start(delta_time);
	timer->start(1);
}

void godot::MenuButtons::_play_effect()
{
	get_parent()->add_child(click_effect->instance());
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