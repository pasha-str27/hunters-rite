#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeAttackJumpState::_fight()
{
	Godot::print("jumping...");
	//	make stuff
	ai->_jump();
	ai->_change_state(new SlimeAttackShootState(ai));
}
