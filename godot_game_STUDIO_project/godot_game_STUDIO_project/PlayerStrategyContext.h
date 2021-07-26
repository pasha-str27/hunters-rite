#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerStrategyContext
	{
		IPlayer* strategy;

	public:
		PlayerStrategyContext();
		~PlayerStrategyContext();
		void _set_strategy(IPlayer* strategy);
		void _process_input();
		void _move();
		void _set_speed(float speed);
		void _fight(Node* node = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _change_can_fight(bool value);
		bool _can_fight();
		void _set_enemy(Node* enemy = nullptr);
		void _take_damage(float damage, bool is_spike = false);
		float _get_HP();
		void _set_HP(float HP);
		void _set_right_HP(float HP);
		float _get_damage();
		void _set_damage(float value);
		void _revive();
		bool _was_revived();
		float _get_max_HP();
		void _set_max_HP(float value);
		void _update_health_bar();
		ProgressBar* _get_health_bar();
		void _stop_animations();
		float _get_special_time();
		void _set_special_time(float value);
		void _stop_special();
		void _start_special();
		bool _get_safe_mode();
		IPlayer* _clone();
		void _set_was_revived(bool value);
		void _heal();
		void _set_controll_buttons(Dictionary input_map);
		void _set_is_attacking(bool value);
		void _decrease_attack_radius();
		void _encrease_attack_radius();
		Dictionary _get_controll_buttons();
	};
}