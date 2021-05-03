#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerController : public KinematicBody2D
	{
	private:
		GODOT_CLASS(PlayerController, KinematicBody2D);
		IPlayer* current_player;
		Ref<PackedScene> bullet_prefab;

		float speed;
		Timer* timer;
		bool can_move;

		int number_to_next_item;
		float attack_speed_delta;
	public:
		static void _register_methods();
		PlayerController();
		~PlayerController();
		void _init();
		void _input(Input* event);
		void _ready();
		void _start_timer();
		void _on_timeout();
		bool _can_fight();
		void _set_enemy(Node* enemy = nullptr);
		void _add_bullet(Node* node);
		void _process(float delta);
		void _take_damage(float damage, bool is_spike = false);
		void _on_Area2D_body_entered(Node* node);
		void _on_Area2D_area_entered(Node* node);
		void _on_Area2D_area_exited(Node* node);
		void _change_can_moving(bool value);
		void change_can_moving_timeout();
		void _decrease_attack_radius();
		void _encrease_attack_radius();
		void _set_number_to_next_item(int value);
		int _get_number_to_next_item();
		void _set_speed(float value);
		float _get_speed();
		void _set_HP(float value);
		float _get_HP();
		void _set_damage(float value);
		float _get_damage();
		void _set_attack_speed_delta(float value);
		float _get_attack_speed_delta();
	};
}
