#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeAttackJumpState::_fight()
{
	//	make stuff
	ai->_jump();
	ai->_change_state(new SlimeAttackShootState(ai));
}

godot::SlimeAttackJumpState::SlimeAttackJumpState(SlimeBossAI* boss) :ISlimeAttackState(boss) {}
