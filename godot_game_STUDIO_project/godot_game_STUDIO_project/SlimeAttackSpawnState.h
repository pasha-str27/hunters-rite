#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class SlimeAttackSpawnState: public ISlimeAttackState
	{
	public:
		void _fight();
		SlimeAttackSpawnState(SlimeBossAI* boss) :ISlimeAttackState(boss){};
	};
}


