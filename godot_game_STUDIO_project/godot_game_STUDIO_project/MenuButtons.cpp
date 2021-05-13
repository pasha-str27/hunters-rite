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
void godot::MenuButtons::_init(){}

void godot::MenuButtons::_ready()
{	
	// Set focus button in Menu and Notise scenes
	set_focus_mode(true);
	
	if (find_parent("root")!=nullptr && !find_parent("root")->has_node("MenuBackMusic"))
	{
		find_parent("root")->call_deferred("add_child", menu_back->instance());
	}

	if (get_name() == "Menu") {
		cast_to<TextureButton>(get_child(1)->get_child(1)->get_child(0))->grab_focus();
	}
	else if (get_name() == "Notice") {
		cast_to<TextureButton>(get_child(1)->get_child(1)->get_child(0)->get_child(0)->get_child(0))->grab_focus();
	}
	else if (get_name() == "Pause") {
		cast_to<TextureButton>(get_child(0)->get_child(0)->get_child(1)->get_child(0)->get_child(0))->grab_focus();
	}
	else {
		cast_to<TextureButton>(get_child(1)->get_child(1)->get_child(0))->grab_focus();
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
	register_method((char*)"_on_Menu_pressed", &MenuButtons::_on_Menu_pressed);
	register_method((char*)"_on_Resume_pressed", &MenuButtons::_on_Resume_pressed);
	register_method((char*)"_play_change_cursor_effect", &MenuButtons::_play_change_cursor_effect);

	register_property<MenuButtons, Ref<PackedScene>>("click_effect", &MenuButtons::click_effect, nullptr);
	register_property<MenuButtons, Ref<PackedScene>>("menu back music", &MenuButtons::menu_back, nullptr);

}

void godot::MenuButtons::_on_Play_pressed(Variant)
{
	_play_effect();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Notice.tscn");
	find_parent("root")->add_child(res->instance());
	queue_free();
}

void godot::MenuButtons::_on_Back_pressed(Variant)
{
	_play_effect();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");

	find_parent("root")->add_child(res->instance());
	queue_free();
}

void godot::MenuButtons::_on_Option_pressed(Variant)
{
	_play_effect();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Option.tscn");
	find_parent("root")->add_child(res->instance());
	queue_free();
}

void godot::MenuButtons::_on_FullScreen_pressed(Variant)
{
	_play_effect();
	//Godot::print("On");
	if (!OS::get_singleton()->is_window_fullscreen()) {
		OS::get_singleton()->set_window_fullscreen(true);
	}
	else OS::get_singleton()->set_window_fullscreen(false);
}

void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	_play_effect();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://main_scene.tscn");

	find_parent("root")->add_child(res->instance());
	queue_free();

	//SceneTree* tree = get_tree();
	//tree->change_scene_to(res);
}

void godot::MenuButtons::_on_Menu_pressed(Variant)
{
	_play_effect();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");

	find_parent("root")->add_child(res->instance());
	queue_free();
}


void godot::MenuButtons::_on_Resume_pressed(Variant)
{
	_play_effect();
	if (get_tree()->is_paused()) {
		get_tree()->set_pause(false);
		queue_free();
	}
}

void godot::MenuButtons::_on_Quit_pressed(Variant)
{
	_play_effect();
	_exit_tree();
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