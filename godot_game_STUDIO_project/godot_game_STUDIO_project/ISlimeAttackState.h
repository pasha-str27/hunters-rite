#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class ISlimeAttackState
	{
	protected:
		SlimeBossAI* ai = nullptr; 
	public:
		static int taken_damage;
		virtual void _fight() {};
		ISlimeAttackState(SlimeBossAI* boss) { ai = boss; };
		~ISlimeAttackState() { ai = nullptr; };
	};
}

