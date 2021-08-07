#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeAttackSpawnState::_fight()
{
	//	make stuff
	ai->_spawn_enemy();
	ai->change_can_fight(true, new SlimeAttackShootState(ai));
}

godot::SlimeAttackSpawnState::SlimeAttackSpawnState(SlimeBossAI* boss) :ISlimeAttackState(boss) {}
