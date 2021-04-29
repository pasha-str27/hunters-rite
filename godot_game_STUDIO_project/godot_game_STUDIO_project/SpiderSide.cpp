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
	register_method("_get_on_body", &SpiderSide::_get_on_body);
	register_method("_on_Area2D_body_exited", &SpiderSide::_on_Area2D_body_exited);
	
	register_property<SpiderSide, int>("side", &SpiderSide::side, -1);
}

void godot::SpiderSide::_on_Area2D_body_entered(Node2D* node)
{
	is_in_boby = true;
	//get_parent()->call("_remove_side", side);
}

void godot::SpiderSide::_on_Area2D_body_exited(Node2D* node)
{
	is_in_boby = false;
}

void godot::SpiderSide::_init()
{
}

bool godot::SpiderSide::_get_on_body()
{
	return is_in_boby;
}

void godot::SpiderSide::_ready()
{
	is_in_boby = false;
}
