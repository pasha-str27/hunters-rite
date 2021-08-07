#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerData : public IPlayer, public KinematicBody2D
	{
		float speed;
		Vector2 dir;
		Node2D* object;
		bool can_fight_value;
		float HP;
		float damage;
		float max_HP;
		bool was_revived;
		float special_time = 0;
		bool is_safe_mode = false;

	public:
		Dictionary input_map;
		static Input* input_controller;

	    ProgressBar* health_bar = nullptr;
		PlayerData(Node2D* object, Ref<PackedScene>bullet = 0);
		PlayerData();
		~PlayerData();
		void _move();
		void _set_speed(float speed);
		void _fight(Node* node = nullptr);
		void _add_bullet(Node* node = nullptr);
		float _get_speed();
		void _set_dir(Vector2 dir);
		Vector2 _get_dir();
		Node2D* _get_object();
		void _take_damage(float damage, bool is_spike);
		void _change_can_fight(bool value);
		bool _can_fight();
		void _process_input();
		void _set_enemy(Node* enemy = nullptr);
		float _get_HP();
		void _set_HP(float HP);
		void _set_right_HP(float HP);
		float _get_damage();
		void _set_damage(float value);
		void _revive();
		bool _was_revived();
		void _set_was_revived(bool value);
		float _get_max_HP();
		void _set_max_HP(float value);
		virtual void _update_health_bar() = 0;
		virtual ProgressBar* _get_health_bar();
		void _stop_animations();
		float _get_special_time();
		void _set_special_time(float value);
		void _set_safe_mode(bool value);
		bool _get_safe_mode();
		void _stop_special();
		void _start_special();
		void _set_controll_buttons(Dictionary input_map);
		Dictionary _get_controll_buttons();
		IPlayer* _clone();
		void _heal();
		void _set_is_attacking(bool value);
		void _decrease_attack_radius();
		void _encrease_attack_radius();
	};
}