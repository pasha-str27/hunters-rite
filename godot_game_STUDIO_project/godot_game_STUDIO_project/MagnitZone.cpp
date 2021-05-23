#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::MagnitZone::_register_methods()
{
	register_method("_init", &MagnitZone::_init);
	register_method("_ready", &MagnitZone::_ready);
	register_method("_process", &MagnitZone::_process);
	register_method("_on_body_entered", &MagnitZone::_on_body_entered);
	register_method("_on_body_exited", &MagnitZone::_on_body_exited);
	register_method("_set_player1", &MagnitZone::_set_player1);
	register_method("_set_player2", &MagnitZone::_set_player2);
}

godot::MagnitZone::MagnitZone()
{
}

void godot::MagnitZone::_init()
{
}

void godot::MagnitZone::_ready()
{
}

void godot::MagnitZone::_process(float delta)
{
	if (player1 != nullptr)
		player1->set_global_position(player1->get_global_position().move_toward(get_global_position(), force * delta));
	
	if (player2 != nullptr)
		player2->set_global_position(player2->get_global_position().move_toward(get_global_position(), force * delta));
}

void godot::MagnitZone::_on_body_entered(Node* node)
{
	if (node->is_in_group("player1"))
		player1 = cast_to<Node2D>(node);

	if (node->is_in_group("player2"))
		player2 = cast_to<Node2D>(node);
}

void godot::MagnitZone::_on_body_exited(Node* node)
{
	if (node->is_in_group("player1"))
		player1 = nullptr;

	if (node->is_in_group("player2"))
		player2 = nullptr;
}

void godot::MagnitZone::_set_player1()
{
	Godot::print("set null pl1");
	player1 = nullptr;
}

void godot::MagnitZone::_set_player2()
{
	Godot::print("set null pl2");
	player2 = nullptr;
}
