#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::SpiderSide::_register_methods()
{
	register_method("_init", &SpiderSide::_init);
	register_method("_ready", &SpiderSide::_ready);
	register_method("_on_Area2D_body_entered", &SpiderSide::_on_Area2D_body_entered);
	
	register_property<SpiderSide, int>("side", &SpiderSide::side, -1);
}

void godot::SpiderSide::_on_Area2D_body_entered(Node2D* node)
{
	Godot::print(node->get_name());
	//get_parent()->call("_remove_side", side);
}

void godot::SpiderSide::_init()
{
}

void godot::SpiderSide::_ready()
{
}
