#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class SlimeAttackShootState: public ISlimeAttackState
	{
	public:
		void _fight();
		SlimeAttackShootState(SlimeBossAI* boss);
	};
}
