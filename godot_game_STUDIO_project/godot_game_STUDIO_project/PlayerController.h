#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class ItemGenerator;

	class PlayerController : public KinematicBody2D
	{
	private:
		GODOT_CLASS(PlayerController, KinematicBody2D);
		IPlayer* current_player;
		Ref<PackedScene> bullet_prefab;
		Ref<PackedScene> revive_zone;
		Node* door = nullptr;

		ItemGenerator* item_generator = nullptr;

		float _hp;
		float _damage;		
		float speed;
		Timer* timer;
		bool can_move;
		bool is_alive;
		bool is_dashing;

		int number_to_next_item;
		float attack_speed_delta;
		float dash_time_delta;
		float dash_cooldown_delta;
		float dash_speed_multiplier;

		Particles2D* hurt_particles = nullptr;
		Particles2D* buff_debuff_particles = nullptr;
		Particles2D* dash_particles = nullptr;
		Particles2D* revive_particles = nullptr;

	public:
		static void _register_methods();
		PlayerController();
		~PlayerController();
		void _init();
		void _input(InputEventKey* event);
		void _ready();
		void _start_timer();
		void _on_timeout();
		void _start_dash_timer();
		void _on_dash_timeout();
		void _start_dash_cooldow_timer();
		void _on_dash_cooldown_timeout();
		bool _can_fight();
		void _change_can_fight(bool value);
		void _set_enemy(Node* enemy = nullptr);
		void _add_bullet(Node* node);
		void _process(float delta);
		void _take_damage(float damage, bool is_spike = false);
		void _on_Area2D_body_entered(Node* node);
		void _on_Area2D_area_entered(Node* node);
		void _on_Area2D_area_exited(Node* node);
		void _change_can_moving(bool value);
		void _change_moving(bool value);
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
		void _die();
		void _revive();
		float _get_max_HP();
		void _set_max_HP(float value);
		void _on_enemy_die(Vector2 enemy_position);
		bool _is_alive();
		void _start_item_particles(bool is_buff);
		void _change_is_dashing_state();
		void _update_health_bar();
		void _update_max_health_bar_size();
		void _animate_spider_web();
		void _show_tutorial_message(Node* node);
		void _hide_tutorial_message(Node* node);
		void _stop_animations();
		void _player_fight();
	};
}
