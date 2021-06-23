#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerMeleeGhost : public PlayerData
	{
		AnimatedSprite* sprite = nullptr;
		AnimatedSprite* vfx_sprite = nullptr;

		AnimationPlayer* animator = nullptr;

	public:
		PlayerMeleeGhost(Node2D* obj, Ref<PackedScene> bullet = 0);
		~PlayerMeleeGhost();
		void _move();
		void _process_input();
		void _set_HP(float value);
		void _heal();
		void _update_health_bar();
		ProgressBar* _get_health_bar();
	};
}
