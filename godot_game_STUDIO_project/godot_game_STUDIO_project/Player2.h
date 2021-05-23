#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Player2 : public PlayerData
	{
		Node* current_enemy;

		AnimatedSprite* sprite = nullptr;
		AnimatedSprite* vfx_sprite = nullptr;

	public:
		Player2(Node2D* obj, Ref<PackedScene> bullet = 0);
		~Player2();
		void _move();
		void _process_input();
		void _fight(Node* node = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _set_enemy(Node* enemy=nullptr);
		void _take_damage(float damage, bool is_spike = false);
		void _set_speed(float speed);
		void _set_HP(float value);
		void _revive();
		void _update_health_bar();
		ProgressBar* _get_health_bar();
		void _stop_animations();
		void _stop_special();
		void _start_special();
	};
}
