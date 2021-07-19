#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerShootDied : public PlayerData
	{
		AnimatedSprite* sprite = nullptr;

	public:
		PlayerShootDied(Node2D* obj, Ref<PackedScene> bullet = 0);
		~PlayerShootDied();
		void _revive();
		void _update_health_bar();
		ProgressBar* _get_health_bar();
	};
}
