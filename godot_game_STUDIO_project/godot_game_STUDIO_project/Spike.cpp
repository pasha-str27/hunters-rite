#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void Spike::_register_methods()
{
	register_method("_init", &Spike::_init);
	register_method("_get_damage", &Spike::_get_damage);
}

Spike::Spike()
{
	this->damage = 5;
}

void Spike::_init()
{
}

float godot::Spike::_get_damage()
{
	return this->damage;
}
