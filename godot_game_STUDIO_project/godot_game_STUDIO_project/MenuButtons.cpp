#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif


using namespace godot;

MenuButtons::MenuButtons() {}
MenuButtons::~MenuButtons() {}
void godot::MenuButtons::_init() {}

void MenuButtons::_register_methods() {

	register_method((char*)"_on_Play_pressed", &MenuButtons::_on_Play_pressed);
	register_method((char*)"_on_Option_pressed", &MenuButtons::_on_Option_pressed);
	register_method((char*)"_on_Quit_pressed", &MenuButtons::_on_Quit_pressed);
	register_method((char*)"_on_Back_pressed", &MenuButtons::_on_Back_pressed);
	register_method((char*)"_on_Flower_pressed", &MenuButtons::_on_Flower_pressed);
	register_property<MenuButtons, Ref<PackedScene>>("game_scene", &MenuButtons::game_scene, nullptr);
}


void godot::MenuButtons::_on_Play_pressed(Variant)
{
	SceneTree* tree = get_tree();
	tree->change_scene_to(game_scene);
}

void godot::MenuButtons::_on_Back_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://title_screen.tscn");
	SceneTree* tree = get_tree();
	tree->change_scene_to(res);
}

void godot::MenuButtons::_on_Option_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://option.tscn");
	SceneTree* tree = get_tree();
	tree->change_scene_to(res);
}

void godot::MenuButtons::_on_Flower_pressed(Variant)
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> res = rld->load("res://main_scene.tscn");
	SceneTree* tree = get_tree();
	tree->change_scene_to(res);
}


void godot::MenuButtons::_on_Quit_pressed(Variant)
{
	//_exit_tree();
	//SceneTree* tree = get_tree();
	//tree->quit();

}
