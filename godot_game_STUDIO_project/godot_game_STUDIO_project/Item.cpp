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
}

void godot::Item::_on_Area2D_body_entered(Node* node)
{
}

void godot::Item::_init()
{
}

void godot::Item::_process()
{
}
