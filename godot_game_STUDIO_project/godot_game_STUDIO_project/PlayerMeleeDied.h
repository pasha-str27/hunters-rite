#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerMeleeDied : public PlayerData
	{
		AnimatedSprite* sprite = nullptr;
		AnimatedSprite* vfx_sprite = nullptr;

		AnimationPlayer* animator = nullptr;

	public:
		PlayerMeleeDied(Node2D* obj, Ref<PackedScene> bullet = 0);
		~PlayerMeleeDied();
		void _revive();
		void _update_health_bar();
		ProgressBar* _get_health_bar();
	};
}
