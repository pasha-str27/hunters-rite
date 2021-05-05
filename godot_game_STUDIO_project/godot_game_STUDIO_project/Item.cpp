#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::Item::_register_methods()
{
	register_method("_ready", &Item::_ready);
	register_method("_init", &Item::_init);
	register_method("_process", &Item::_process);
	register_method("_on_Area2D_body_entered", &Item::_on_Area2D_body_entered);

	register_property<Item, float>("speed", &Item::speed, 1000);
	register_property<Item, float>("HP", &Item::HP, 1000);
	register_property<Item, float>("damage", &Item::damage, 1000);
	register_property<Item, float>("attack_speed_delta", &Item::attack_speed_delta, 1000);
	register_property<Item, int>("number_to_next_item", &Item::number_to_next_item, 1000);
	register_property<Item, bool>("decrease_attack_radius", &Item::decrease_attack_radius, false);
	register_property<Item, bool>("encrease_attack_radius", &Item::encrease_attack_radius, false);
}

godot::Item::Item()
{
}

godot::Item::~Item()
{
}

void godot::Item::_ready()
{
	Godot::print("vvvv");
	//	get animator
	animator = cast_to<AnimationPlayer>(get_child(0)->get_child(0));
	//	start animation
	animator->play("idle");
	//	stop animation
	//animator->stop();
}

void godot::Item::_on_Area2D_body_entered(Node* node)
{
	Godot::print("zzzz");
	if (!node->is_in_group("player"))
		return;

	node->call("_set_speed", (float)node->call("_get_speed") + speed);//++
	node->call("_set_HP", (float)node->call("_get_HP") + HP);//++
	node->call("_set_damage", (float)node->call("_get_damage") + damage);//++
	node->call("_set_number_to_next_item", (int)node->call("_get_number_to_next_item") + number_to_next_item);//+++
	node->call("_set_attack_speed_delta", (float)node->call("_get_attack_speed_delta") + attack_speed_delta);

	//++
	if (node->is_in_group("player2"))
	{
		if (decrease_attack_radius)
			node->call("_decrease_attack_radius");

		//+++++
		if (encrease_attack_radius)
			node->call("_encrease_attack_radius");
	}

	queue_free();
}

void godot::Item::_init()
{
}

void godot::Item::_process()
{
}
