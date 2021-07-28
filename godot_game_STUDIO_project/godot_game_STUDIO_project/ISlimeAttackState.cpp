#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::ISlimeAttackState::ISlimeAttackState(SlimeBossAI* boss)
{
	ai = boss;
}

godot::ISlimeAttackState::~ISlimeAttackState()
{
	ai = nullptr;
}
