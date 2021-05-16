#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::ExitHandler::_register_methods()
{
	register_method("_ready", &ExitHandler::_ready);
	register_method("_on_Area2D_area_entered", &ExitHandler::_on_Area2D_area_entered);
	register_method("_on_Area2D_area_exited", &ExitHandler::_on_Area2D_area_exited);
	register_method("_load_menu_scene", &ExitHandler::_load_menu_scene);	

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
	{
		if (PlayersContainer::_get_instance()->_get_player1() != nullptr)
			PlayersContainer::_get_instance()->_get_player1()->call("_change_can_moving", false);

		if (PlayersContainer::_get_instance()->_get_player2() != nullptr)
			PlayersContainer::_get_instance()->_get_player2()->call("_change_can_moving", false);

		auto fade = cast_to<Node2D>(fade_out->instance());
		CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->add_child(fade);
		fade->get_child(0)->get_child(0)->call("_set_is_exit_anim", true);
	}
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
