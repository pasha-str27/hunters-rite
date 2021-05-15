#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::ExitHandler::_register_methods()
{
	register_method("_ready", &ExitHandler::_ready);
	register_method("_on_Area2D_area_entered", &ExitHandler::_on_Area2D_area_entered);
	register_method("_on_Area2D_area_exited", &ExitHandler::_on_Area2D_area_exited);
	
	register_property<ExitHandler, Ref<PackedScene>>("Fade Out", &ExitHandler::fade_out, nullptr);
}

void godot::ExitHandler::_init()
{
}

void godot::ExitHandler::_ready()
{
	ResourceLoader* resource_loader = ResourceLoader::get_singleton();
	menu_scene = resource_loader->load("res://Assets/Prefabs/Scenes/Menu.tscn");
}

void godot::ExitHandler::_on_Area2D_area_entered(Node* other)
{
	if (other->is_in_group("player"))
		players_count++;

	bool is_only_one_alive = CustomExtensions::IsOnlyOnePlayerAlive(other);
	if (is_only_one_alive || (players_count == 2))
		_load_menu_scene();
}

void godot::ExitHandler::_on_Area2D_area_exited(Node* other)
{
	if (other->is_in_group("player"))
		players_count--;
}

void godot::ExitHandler::_load_menu_scene()
{
	SceneTree* tree = get_tree();
	get_node("/root")->add_child(menu_scene->instance());
	get_parent()->get_parent()->queue_free();
}

godot::ExitHandler::ExitHandler()
{
}

godot::ExitHandler::~ExitHandler()
{
}
