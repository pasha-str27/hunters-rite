#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void Spike::_register_methods()
{
	register_method("_init", &Spike::_init);
	register_method((char*)"_ready", &Spike::_ready);
	register_method("_get_damage", &Spike::_get_damage);
}

Spike::Spike()
{
	this->damage = 5;
}

Spike::~Spike()
{
}

void Spike::_init()
{
}

void godot::Spike::_ready()
{
}

float godot::Spike::_get_damage()
{
	return this->damage;
}
