#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif


using namespace godot;

MenuButtons::MenuButtons() {}
MenuButtons::~MenuButtons() {}
void godot::MenuButtons::_init(){}

void godot::MenuButtons::_ready()
{	
	// Set focus button in Menu and Notise scenes
	set_focus_mode(true);

	if (get_name() == "Menu"){
		cast_to<TextureButton>(get_child(1)->get_child(1)->get_child(0))->grab_focus();
	}
	else if (get_name() == "Notice"){
		cast_to<TextureButton>(get_child(1)->get_child(1)->get_child(0)->get_child(0)->get_child(0))->grab_focus();
	}
	else{
		cast_to<TextureButton>(get_child(1)->get_child(1)->get_child(0))->grab_focus();
	}
}


void MenuButtons::_register_methods() {

	register_method((char*)"_ready", &MenuButtons::_ready);
	register_method((char*)"_on_Play_pressed", &MenuButtons::_on_Play_pressed);
	register_method((char*)"_on_Option_pressed", &MenuButtons::_on_Option_pressed);
	register_method((char*)"_on_Quit_pressed", &MenuButtons::_on_Quit_pressed);
	register_method((char*)"_on_Back_pressed", &MenuButtons::_on_Back_pressed);
	register_method((char*)"_on_Flower_pressed", &MenuButtons::_on_Flower_pressed);
	register_method((char*)"_on_FullScreen_pressed", &MenuButtons::_on_FullScreen_pressed);
}

void godot::MenuButtons::_on_Play_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Notice.tscn");
	get_parent()->add_child(res->instance());
	queue_free();
	//SceneTree* tree = get_tree();
	//tree->free();
}

void godot::MenuButtons::_on_Back_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");

	get_parent()->add_child(res->instance());
	queue_free();
	//SceneTree* tree = get_tree();
	//tree->change_scene_to(res);

}

void godot::MenuButtons::_on_Option_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://Assets/Prefabs/Scenes/Option.tscn");
	get_parent()->add_child(res->instance());
	queue_free();
	//SceneTree* tree = get_tree();
	//tree->change_scene_to(res);
}
void godot::MenuButtons::_on_FullScreen_pressed(Variant)
{
	Godot::print("On");
	if (!OS::get_singleton()->is_window_fullscreen()) {
		OS::get_singleton()->set_window_fullscreen(true);
	}
	else OS::get_singleton()->set_window_fullscreen(false);
}

void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	//Ref<PackedScene> res = rld->load("res://main_scene.tscn");
	SceneTree* tree = get_tree();
	//tree->change_scene_to(res);
}


void godot::MenuButtons::_on_Quit_pressed(Variant)
{
	_exit_tree();
}