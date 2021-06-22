#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerMelee : public PlayerData
	{
		Node* current_enemy;

		AnimatedSprite* sprite = nullptr;
		AnimatedSprite* vfx_sprite = nullptr;

		AnimationPlayer* animator = nullptr;

	public:
		PlayerMelee(Node2D* obj, Ref<PackedScene> bullet = 0);
		~PlayerMelee();
		void _move();
		void _process_input();
		void _fight(Node* node = nullptr);
		void _set_enemy(Node* enemy = nullptr);
		void _take_damage(float damage, bool is_spike = false);
		void _set_HP(float value);
		void _update_health_bar();
		ProgressBar* _get_health_bar();
		void _stop_animations();
		void _stop_special();
		void _start_special();
	};
}
