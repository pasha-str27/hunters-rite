#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Sword::_register_methods()
{
	register_method((char*)"_init", &Sword::_init);
	register_method((char*)"_on_Area2D_body_entered", &Sword::_on_Area2D_body_entered);
	register_method((char*)"_on_Area2D_body_exited", &Sword::_on_Area2D_body_exited);
}

godot::Sword::~Sword()
{
}

void godot::Sword::_init()
{
}

void godot::Sword::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("enemy"))
		get_parent()->call("_set_enemy", node);
}

void godot::Sword::_on_Area2D_body_exited(Node* node)
{
	if (node->is_in_group("enemy"))
		get_parent()->call("_set_enemy");
}
