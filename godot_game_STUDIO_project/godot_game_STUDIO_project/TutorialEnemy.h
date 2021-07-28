#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class TutorialEnemy: public KinematicBody2D
	{
	private:
		GODOT_CLASS(TutorialEnemy, KinematicBody2D);
		float _hp;
		AnimatedSprite* sprite;
		ProgressBar* health_bar;
		Timer* timer;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _take_damage(float damage, int player_id);
		void _on_damage_animation_finished();
		void _on_spawn_end();
		TutorialEnemy();
		~TutorialEnemy();
	};
}


