#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

bool Sword::is_enemy_on_sword = false;

void godot::Sword::_register_methods()
{
	register_method((char*)"_process", &Sword::_process);
	register_method((char*)"_ready", &Sword::_ready);
	register_method((char*)"_init", &Sword::_init);
	register_method((char*)"_on_Area2D_body_entered", &Sword::_on_Area2D_body_entered);
	register_method((char*)"_on_Area2D_body_exited", &Sword::_on_Area2D_body_exited);

	register_property<Sword, float>("speed", &Sword::damage, 10);
}

godot::Sword::Sword()
{
	damage = 10;
}

godot::Sword::~Sword()
{
}

void godot::Sword::_init()
{
}

void godot::Sword::_ready()
{
}

void godot::Sword::_process()
{
}

void godot::Sword::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("enemy"))
	{
		get_parent()->call("_set_enemy", node);
	}
}

void godot::Sword::_on_Area2D_body_exited(Node* node)
{
	if (node->is_in_group("enemy"))
	{
		get_parent()->call("_set_enemy");
	}
}
