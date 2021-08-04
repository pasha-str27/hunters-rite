#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerShootGhost : public PlayerData
	{
		AnimatedSprite* sprite = nullptr;

	public:
		PlayerShootGhost(Node2D* obj, Ref<PackedScene> bullet = 0);
		~PlayerShootGhost();
		void _move();
		void _process_input();
		void _update_health_bar();
		ProgressBar* _get_health_bar();
		void _heal();
		//void _stop_animations();
	};
}
