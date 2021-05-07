#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::EnemySideChecker::_register_methods()
{
	register_method("_init", &EnemySideChecker::_init);
	register_method("_ready", &EnemySideChecker::_ready);
	register_method("_on_Area2D_body_entered", &EnemySideChecker::_on_Area2D_body_entered);
	register_method("_get_on_body", &EnemySideChecker::_get_on_body);
	register_method("_get_current_node", &EnemySideChecker::_get_current_node);
	register_method("_on_Area2D_body_exited", &EnemySideChecker::_on_Area2D_body_exited);
	
	register_property<EnemySideChecker, int>("side", &EnemySideChecker::side, -1);
}

void godot::EnemySideChecker::_on_Area2D_body_entered(Node2D* node)
{
	Godot::print(node->get_name());
	is_in_boby = true;
	current_node = node;
}

void godot::EnemySideChecker::_on_Area2D_body_exited(Node2D* node)
{
	is_in_boby = false;
	current_node = nullptr;
}

void godot::EnemySideChecker::_init()
{
}

bool godot::EnemySideChecker::_get_on_body()
{
	return is_in_boby;
}

void godot::EnemySideChecker::_ready()
{
	is_in_boby = false;
	current_node = nullptr;
}

Node2D* godot::EnemySideChecker::_get_current_node()
{
	return current_node;
}