#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeAttackSpawnState::_fight()
{
	Godot::print("spawning...");
	//	make stuff
	ai->_spawn_enemy();
	ai->_wait(3);
	ai->_change_state(new SlimeAttackJumpState(ai));
}
