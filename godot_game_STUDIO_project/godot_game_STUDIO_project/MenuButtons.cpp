#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

bool MenuButtons::was_focused = false;

MenuButtons::MenuButtons() 
{
	was_focused = false;
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
	
	std::vector<String> name_buttons{"Play", "Flower_button", "Back"};

	if (find_parent("root")!=nullptr && !find_parent("root")->has_node("MenuBackMusic"))
	{
		find_parent("root")->call_deferred("add_child", menu_back->instance());
	}

	// Set focus button 
	set_focus_mode(true);
	for (auto name : name_buttons)
	{
		if (find_node(name) != nullptr) {
			cast_to<TextureButton>(find_node(name))->grab_focus();
			break;
		}
	}

	save_game();
	load_game();
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
	register_method((char*)"save", &MenuButtons::save);

	register_property<MenuButtons, Ref<PackedScene>>("click_effect", &MenuButtons::click_effect, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("menu back music", &MenuButtons::menu_back, nullptr);

}

void godot::MenuButtons::save_game()
{
	Godot::print("ssss");
	auto save_game = File::_new();
	save_game->open("user://savegame.save", File::WRITE);

	auto save_nodes = get_tree()->get_nodes_in_group("a");

	for (int i = 0; i < save_nodes.size(); ++i)
	{
		auto node_data = cast_to<Node>(save_nodes[i])->call("save");

		save_game->store_line(node_data);
	}
	save_game->close();
}


void godot::MenuButtons::load_game()
{
	auto save_game = File::_new();
	if (!save_game->file_exists("user://savegame.save"))
		return; // Error!We don't have a save to load.

	save_game->open("user://savegame.save", File::READ);

	while (save_game->get_position() < save_game->get_len())
	{
		
		Dictionary node_data = JSON::get_singleton()->parse(save_game->get_line())->get_result();
		Godot::print(node_data.values()[0]);
	}

	save_game->close();
}

String godot::MenuButtons::save()
{
	Dictionary save_dict;
	save_dict=Dictionary::make("a",25);
	return save_dict.to_json();
}


void godot::MenuButtons::_on_Play_pressed(Variant)
{
	_play_effect();
	get_parent()->add_child(notice_scene->instance());
	queue_free();
}


void godot::MenuButtons::_on_Back_pressed(Variant)
{
	//_play_effect();
	find_parent("root")->add_child(menu_scene->instance());
	queue_free();
}


void godot::MenuButtons::_on_Option_pressed(Variant)
{
	_play_effect();
	get_parent()->add_child(option_scene->instance());
	queue_free();	
}


void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	//_play_effect();
	get_tree()->change_scene_to(game_scene);
	queue_free();
}


void godot::MenuButtons::_on_Quit_pressed(Variant)
{
	_play_effect();
	_exit_tree();
}


void godot::MenuButtons::_on_FullScreen_pressed(Variant)
{
	_play_effect();
	if (!OS::get_singleton()->is_window_fullscreen()) {
		OS::get_singleton()->set_window_fullscreen(true);
	}
	else OS::get_singleton()->set_window_fullscreen(false);
}


void godot::MenuButtons::_on_effects_value_changed(float value)
{
	Godot::print(String::num(value));
}

void godot::MenuButtons::_on_music_value_changed(float value)
{
	Godot::print(String::num(value));
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