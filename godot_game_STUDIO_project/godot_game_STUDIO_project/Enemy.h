#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D);

		float HP;

		public:
			static void _register_methods();
			Enemy();
			~Enemy();
			void _init();
			void _ready();
			void _process();
			void _take_damage(float damage);
	};
}