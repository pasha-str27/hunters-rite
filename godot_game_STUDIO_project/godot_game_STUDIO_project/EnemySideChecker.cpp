#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::EnemySideChecker::~EnemySideChecker()
{
	current_node = nullptr;
}

void godot::EnemySideChecker::_register_methods()
{
	register_method("_init", &EnemySideChecker::_init);
	register_method("_ready", &EnemySideChecker::_ready);
	register_method("_on_Area2D_body_entered", &EnemySideChecker::_on_Area2D_body_entered);
	register_method("_get_on_body", &EnemySideChecker::_get_on_body);
	register_method("_get_current_node", &EnemySideChecker::_get_current_node);
	register_method("_on_Area2D_body_exited", &EnemySideChecker::_on_Area2D_body_exited);
	register_method("_get_side", &EnemySideChecker::_get_side);
	
	register_property<EnemySideChecker, int>("side", &EnemySideChecker::side, -2);
}

void godot::EnemySideChecker::_on_Area2D_body_entered(Node2D* node)
{
	if (node->get_name()=="wall" || node->get_name()=="flower" || node->get_name()=="spike" || node->get_name() == "stone" || node->get_name() == "roof" || node->is_in_group("player"))
	{
		is_in_boby = true;
		current_node = node;
	}
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
	if (side == -1)
		return true;

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


int godot::EnemySideChecker::_get_side()
{
	return side;
}
