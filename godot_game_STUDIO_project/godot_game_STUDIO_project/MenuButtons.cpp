#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

bool MenuButtons::was_focused = false;
bool MenuButtons::was_loaded = false;
bool MenuButtons::is_full_screen = false;
float MenuButtons::music_audio_level = -12.5;
float MenuButtons::effect_audio_level = 6;
GameMode MenuButtons::game_mode = SHOOTER;
AudioStreamPlayer2D* MenuButtons::audio = nullptr;

MenuButtons::MenuButtons()
{
	click_counter = 0;
	was_quit_focused = false;
	was_mode_focused = false;
	was_focused = false;
	delta_time = 1.0 / 50;
	single_mode = true;
}

MenuButtons::~MenuButtons() {
	audio_server = nullptr;
	timer = nullptr;
	timer_music_out = nullptr;
	timer_music = nullptr;
}

void godot::MenuButtons::_init() {}

void godot::MenuButtons::_ready()
{
	audio_server = AudioServer::get_singleton();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	menu_scene = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	option_scene = rld->load("res://Assets/Prefabs/Scenes/Option.tscn");
	notice_scene = rld->load("res://Assets/Prefabs/Scenes/Notice.tscn");
	authors_scene = rld->load("res://Assets/Prefabs/Scenes/Authors.tscn");
	items_scene = rld->load("res://Assets/Prefabs/Scenes/Items.tscn");
	choose_player_scene = rld->load("res://Assets/Prefabs/Scenes/ChoosePlayer.tscn");
	items_grid = rld->load("res://Assets/Prefabs/Scenes/ChoosePlayer.tscn");
	game_scene = rld->load("res://main_scene.tscn");

	cast_to<Camera2D>(get_parent())->_set_current(true);

	// Set focus button in Menu and Notise scenes
	set_focus_mode(true);

	std::vector<String> name_buttons{ "Play", "Flower_button","Melee", "Back", "Resume", "Retry" };

	if (get_name() == "Menu" && find_parent("root") != nullptr && !find_parent("root")->has_node("MenuBackMusic"))
	{
		audio = cast_to<AudioStreamPlayer2D>(menu_back->instance());
		find_parent("root")->call_deferred("add_child", audio);
	}

	for (auto name : name_buttons)
		if (find_node(name) != nullptr)
		{
			cast_to<TextureButton>(find_node(name))->grab_focus();
			break;
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
	register_method((char*)"_on_Items_pressed", &MenuButtons::_on_Items_pressed);
	register_method((char*)"_on_Items_pause_pressed", &MenuButtons::_on_Items_pause_pressed);
	register_method((char*)"_on_FullScreen_pressed", &MenuButtons::_on_FullScreen_pressed);
	register_method((char*)"_on_Back_pause_pressed", &MenuButtons::_on_Back_pause_pressed);
	register_method((char*)"_play_change_cursor_effect", &MenuButtons::_play_change_cursor_effect);
	register_method((char*)"_on_Quit_focus", &MenuButtons::_on_Quit_focus);
	register_method((char*)"_on_Mode_focus", &MenuButtons::_on_Mode_focus);
	register_method((char*)"_set_vertical_scroll", &MenuButtons::_set_vertical_scroll);
	register_method((char*)"_on_animated_focus_entered", &MenuButtons::_on_animated_focus_entered);
	register_method((char*)"_on_animated_focus_exited", &MenuButtons::_on_animated_focus_exited);
	register_method((char*)"_show_chapter_sprite", &MenuButtons::_show_chapter_sprite);
	register_method((char*)"_on_effects_value_changed", &MenuButtons::_on_effects_value_changed);
	register_method((char*)"_on_music_value_changed", &MenuButtons::_on_music_value_changed);
	register_method((char*)"_timeout", &MenuButtons::_timeout);
	register_method((char*)"_start_game", &MenuButtons::_start_game);
	register_method((char*)"_change_audio_volume", &MenuButtons::_change_audio_volume);
	register_method((char*)"_on_Resume_pressed", &MenuButtons::_on_Resume_pressed);
	register_method((char*)"_on_Menu_pressed", &MenuButtons::_on_Menu_pressed);
	register_method((char*)"_on_Retry_pressed", &MenuButtons::_on_Retry_pressed);
	register_method((char*)"_move_to_main_menu", &MenuButtons::_move_to_main_menu);
	register_method((char*)"_audio_fade_to_main_menu", &MenuButtons::_audio_fade_to_main_menu);
	register_method((char*)"_fade_audio", &MenuButtons::_fade_audio);
	register_method((char*)"_input", &MenuButtons::_input);
	register_method((char*)"_reload_scene", &MenuButtons::_reload_scene);

	register_property<MenuButtons, Ref<PackedScene>>("click_effect", &MenuButtons::click_effect, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("menu back music", &MenuButtons::menu_back, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("fade", &MenuButtons::fade, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("fade_in", &MenuButtons::fade_in, nullptr);
}

void godot::MenuButtons::_start_game(int name)
{
	GameManager::show_tutorial = true;
	game_mode = GameMode(name);
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

	timer_music->start(0.01);
	timer->start(1);
}

void godot::MenuButtons::save_game()
{

	auto save_game = File::_new();
	save_game->open("user://savegame_hunters.save", File::WRITE);

	Dictionary save_dict;
	save_dict = Dictionary::make("effect_level", effect_audio_level, "music_level", music_audio_level, "full_screen", is_full_screen);
	save_dict.to_json();

	save_game->store_line(save_dict.to_json());
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

void godot::MenuButtons::_set_animated_focus(String button_name, String animated_name, bool focus_mode)
{
	auto animation = cast_to<AnimationPlayer>(get_parent()->find_node(animated_name));
	auto focus_sprite = cast_to<TextureRect>(get_parent()->find_node(button_name)->get_child(0));
	
	focus_sprite->set_visible(focus_mode);
	
	if (focus_mode)
		animation->play("Focus_scale");
	else
		animation->stop();
}

void godot::MenuButtons::_change_button_name()
{
	_play_change_cursor_effect();
	auto mode_label = cast_to<Label>(find_node("ModeText"));

	if (single_mode)
		mode_label->set_text("Single");
	else
		mode_label->set_text("Cooperative");

}

void godot::MenuButtons::_set_vertical_scroll(int scroll_value)
{
	cast_to<ScrollContainer>(get_parent()->find_node("ScrollContainer"))->set_v_scroll(scroll_value);
}

void godot::MenuButtons::_input(Input* event)
{
	auto ui_left_press = Input::get_singleton()->is_action_just_pressed("ui_left");
	auto ui_right_press = Input::get_singleton()->is_action_just_pressed("ui_right");

	// secret menu
	if (ui_left_press && was_quit_focused)
	{
		click_counter++;

		if (click_counter > 7)
			cast_to<Label>(find_node("QuitLabel"))->set_text("Authors");
	}

	// change coop/single mode
	if ((ui_left_press || ui_right_press) && was_mode_focused)
	{
		single_mode = !single_mode;
		_change_button_name();
	}

	// press buttons in pause
	if (Input::get_singleton()->is_action_just_pressed("ui_pause"))
	{
		Input::get_singleton()->action_release("ui_pause");

		if (get_name() == "Pause")
		{
			get_tree()->set_pause(false);
			cast_to<Camera2D>(get_node("/root/Node2D/Node/Camera2D"))->_set_current(true);
			get_parent()->queue_free();
			return;
		}

		if (get_name() == "Menu")
		{
			_exit_tree();
			return;
		}

		if (get_name() == "Option" || get_name() == "Notice")
		{
			get_node("/root")->add_child(menu_scene->instance());
			get_parent()->queue_free();
			return;
		}
	}
}

// -------Menu buttons-------
void godot::MenuButtons::_on_Play_pressed(Variant)
{
	change_scene(notice_scene);
}

void godot::MenuButtons::_on_Option_pressed(Variant)
{
	change_scene(option_scene);
}

void godot::MenuButtons::_on_Items_pressed(Variant)
{
	change_scene(items_scene);
}

void godot::MenuButtons::_on_Back_pressed(Variant)
{
	change_scene(menu_scene);
}

void godot::MenuButtons::_on_Quit_pressed(Variant)
{
	if (click_counter > 7)
	{
		click_counter = 0;
		change_scene(authors_scene);
		return;
	}
	_play_effect();
	_exit_tree();
}

// -------Notice buttons-------
void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	if (single_mode)
	{
		change_scene(choose_player_scene);
		return;
	}
	game_mode = COOP;
	_start_game(game_mode);
}

// -------Choose chapter-------
void godot::MenuButtons::_show_chapter_sprite(String sprite_name, String description_name, bool mode)
{
	if (this->find_node(sprite_name)->get_child(0)->has_node("AnimationPlayer"))
	{
		if (mode)
			cast_to<AnimationPlayer>(this->find_node(sprite_name)->get_child(0)->get_child(0))->play("idle");
		else
			cast_to<AnimationPlayer>(this->find_node(sprite_name)->get_child(0)->get_child(0))->stop();
	}	

	cast_to<CenterContainer>(this->find_node(sprite_name))->set_visible(mode);
	cast_to<Label>(this->find_node(description_name))->set_visible(mode);

}

// -------Option buttons-------
void godot::MenuButtons::_on_FullScreen_pressed(Variant)
{
	_play_effect();
	is_full_screen = !is_full_screen;
	OS::get_singleton()->set_window_fullscreen(is_full_screen);
	save_game();

}

void godot::MenuButtons::_on_effects_value_changed(float value)
{
	if (value <= -34)
		value = -80;

	effect_audio_level = value;
	audio_server->set_bus_volume_db(1, value);

	save_game();
}

void godot::MenuButtons::_on_music_value_changed(float value)
{
	if (value <= -34)
		value = -80;

	music_audio_level = value;
	audio_server->set_bus_volume_db(2, value);

	save_game();
}

// -------Pause buttons-------
void godot::MenuButtons::_on_Resume_pressed(Input*)
{
	_play_effect();
	get_tree()->set_pause(false);
	cast_to<Camera2D>(get_node("/root/Node2D/Node/Camera2D"))->_set_current(true);
	get_parent()->queue_free();
}

void godot::MenuButtons::_on_Items_pause_pressed(Input*)
{
	_play_effect();
	cast_to<Control>(get_parent()->find_node("Items_in_pause"))->set_visible(true);
	this->set_visible(false);
	cast_to<TextureButton>(get_parent()->find_node("Back_button")->get_child(0))->grab_focus();

}

void godot::MenuButtons::_on_Retry_pressed(Variant)
{
	_play_effect();
	add_child(fade->instance());

	if (timer == nullptr)
	{
		timer = Timer::_new();
		add_child(timer);
	}

	timer->connect("timeout", this, "_reload_scene");

	if (timer_music_out == nullptr)
	{
		timer_music_out = Timer::_new();
		add_child(timer_music_out);
	}

	timer_music_out->connect("timeout", this, "_audio_fade_to_main_menu");

	timer_music_out->start(0.01);
	timer->start(1);
}

void godot::MenuButtons::_on_Menu_pressed(Input*)
{
	_play_effect();
	if (get_name() == "Pause" || get_name() == "GameOver")
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

// -------Items menu in pause button-------
void godot::MenuButtons::_on_Back_pause_pressed(Input*)
{
	_play_effect();
	cast_to<Control>(get_parent()->find_node("Items_in_pause"))->set_visible(false);
	this->set_visible(true);
	cast_to<TextureButton>(get_parent()->find_node("Resume"))->grab_focus();
}

// -------Focus mode on buttons-------
void godot::MenuButtons::_on_Quit_focus(bool mode)
{
	if (mode) {
		was_quit_focused = mode;
		return;
	}
	was_quit_focused = mode;
	click_counter = 0;
	cast_to<Label>(find_node("QuitLabel"))->set_text("Quit");
}

void godot::MenuButtons::_on_Mode_focus()
{
	was_mode_focused = !was_mode_focused;
}

void godot::MenuButtons::_on_animated_focus_entered(String button_name, String animated_name)
{
	_set_animated_focus(button_name, animated_name, true);
}

void godot::MenuButtons::_on_animated_focus_exited(String button_name, String animated_name)
{
	_set_animated_focus(button_name, animated_name, false);
}

//--------------------------------------------------------------------------------------------------------

// -------Work with scenes-------
void godot::MenuButtons::_reload_scene()
{
	GameManager::show_tutorial = true;
	timer->disconnect("timeout", this, "_reload_scene");
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://main_scene.tscn");

	get_node("/root/Node2D")->set_name("to_delete");
	get_tree()->set_pause(false);
	Enemies::get_singleton()->_clear();
	get_node("/root")->add_child(res->instance(), true);
	get_node("/root/to_delete")->queue_free();
}

void godot::MenuButtons::_move_to_main_menu()
{
	get_tree()->set_pause(false);
	ResourceLoader* rld = ResourceLoader::get_singleton();
	menu_scene = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	get_node("/root")->add_child(menu_scene->instance());
	get_node("/root/Node2D")->queue_free();
	get_parent()->queue_free();
	PlayersContainer::_get_instance()->_clear();
}

void  godot::MenuButtons::change_scene(Ref<PackedScene>& scene) 
{
	_play_effect();
	get_node("/root")->add_child(scene->instance());
	get_parent()->queue_free();
}

// -------Audio changes-------
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

void godot::MenuButtons::_change_audio_volume()
{
	if (AudioController::get_singleton()->_change_audio_volume(timer_music, this, audio, delta_time))
		return;
}

void godot::MenuButtons::_audio_fade_to_main_menu()
{
	if (AudioController::get_singleton()->_audio_fade_to_main_menu(timer_music_out, this))
		return;
}

void godot::MenuButtons::_fade_audio()
{
	if (AudioController::get_singleton()->_fade_audio(timer_music, this))
		return;
}

