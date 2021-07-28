#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class SlimeAttackJumpState: public ISlimeAttackState
	{
	public:
		void _fight();
		SlimeAttackJumpState(SlimeBossAI* boss);
	};
}

