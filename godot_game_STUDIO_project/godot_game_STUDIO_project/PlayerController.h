#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class ItemGenerator;
	class PlayerProduce;
	class PlayerStrategyContext;

	class PlayerController : public KinematicBody2D
	{
	private:
		GODOT_CLASS(PlayerController, KinematicBody2D);

		IPlayer* prev_state = nullptr;
		PlayerStrategyContext* current_player_strategy = nullptr;
		PlayerProduce* player_producer = nullptr;
		Ref<PackedScene> bullet_prefab;
		Ref<PackedScene> revive_zone;
		Node* door = nullptr;

		ItemGenerator* item_generator = nullptr;

		bool is_ghost_mode = false;
		float _hp;
		float _damage;		
		float speed;
		float _saved_speed;
		Timer* timer;
		Timer* timer_poison;
		bool can_move;
		bool is_alive;
		bool is_special;
		float diff;

		float attack_speed_delta;
		float dash_time_delta;
		float dash_cooldown_delta;
		float dash_speed_multiplier;

		Particles2D* hurt_particles = nullptr;
		Particles2D* buff_debuff_particles = nullptr;
		Particles2D* dash_particles = nullptr;
		Particles2D* revive_particles = nullptr;
		Particles2D* ghost_end_particles = nullptr;

		Node* camera_shake = nullptr;
		AnimatedSprite* ghost_sprite = nullptr;

	public:
		static void _register_methods();
		PlayerController();
		~PlayerController();
		void _init();
		void _ready();
		void _start_timer();
		void _on_timeout();
		void _start_special_timer();
		void _on_special_timeout();
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
		void _heal();
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
		void _stop_animations();
		void _player_fight();
		void _restore_data();
		void _stay_ghost();
		void _set_was_revived(bool value);
		void _ghost_to_player();
		bool _is_ghost_mode();
		void _set_controll_buttons(String move_up, String move_down, String move_left, String move_right,
			String fight_up, String fight_down, String fight_left, String fight_right, String special);
		void _stop_moving();
		void _continue_moving();
		void _set_is_attacking(bool value);
		void _set_right_HP(float value);
		void _on_ghost_hide();
		void _flip_ghost(bool value);
		void _take_poison();
		void _on_poison_end();
		void _player_to_ghost();
	};
}
