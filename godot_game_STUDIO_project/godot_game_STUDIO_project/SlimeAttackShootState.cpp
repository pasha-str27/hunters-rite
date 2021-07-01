#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeAttackShootState::_fight()
{
	Godot::print("shooting...");
	//	make stuff
	ai->_set_target();
	ai->_shoot();
	ai->_change_state(new SlimeAttackJumpState(ai));
}
