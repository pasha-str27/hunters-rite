#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::Enemy::_register_methods()
{
	register_method("_ready", &Enemy::_ready);
	register_method("_init", &Enemy::_init);
	register_method("_process", &Enemy::_process);
	register_method("take_damage", &Enemy::take_damage);

	register_property<Enemy, float>("HP", &Enemy::HP, 99);
}

godot::Enemy::Enemy()
{
	HP = 100;
}

godot::Enemy::~Enemy()
{
}

void godot::Enemy::_init()
{
}

void godot::Enemy::_ready()
{
}

void godot::Enemy::_process()
{
}

void godot::Enemy::take_damage(float damage)
{
	HP -= damage;

	if (HP <= 0)
		queue_free();
}
