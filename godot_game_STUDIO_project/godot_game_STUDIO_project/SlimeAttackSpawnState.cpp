#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeAttackSpawnState::_fight()
{
	Godot::print("spawning...");
	Godot::print(taken_damage);
	//	make stuff
	if (taken_damage >= 5)
	{
		ai->_spawn_enemy();
		taken_damage = 0;
	}
	ai->change_can_fight(true, new SlimeAttackShootState(ai));
}
