#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::EnemyPrice::_register_methods()
{
	register_method("_init", &EnemyPrice::_init);
	register_method("_get_enemy_price", &EnemyPrice::_get_enemy_price);

	register_property< EnemyPrice, float>("enemy_price", &EnemyPrice::enemy_price, -1);
}

void godot::EnemyPrice::_init()
{
}

float godot::EnemyPrice::_get_enemy_price()
{
	return enemy_price;
}
