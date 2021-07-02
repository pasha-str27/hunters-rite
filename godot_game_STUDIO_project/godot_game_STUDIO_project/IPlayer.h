#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class IPlayer
	{
	public:
		virtual void _process_input() = 0;
		virtual void _move() = 0;
		virtual void _set_speed(float speed) = 0;
		virtual void _fight(Node* node = nullptr) = 0;
		virtual void _add_bullet(Node* node = nullptr) = 0;
		virtual void _change_can_fight(bool value) = 0;
		virtual bool _can_fight() = 0;
		virtual void _set_enemy(Node* enemy = nullptr) = 0;
		virtual void _take_damage(float damage, bool is_spike = false) = 0;
		virtual float _get_HP() = 0;
		virtual void _set_HP(float HP) = 0;
		virtual float _get_damage() = 0;
		virtual void _set_damage(float value) = 0;
		virtual void _revive() = 0;
		virtual bool _was_revived() = 0;
		virtual float _get_max_HP() = 0;
		virtual void _set_max_HP(float value) = 0;
		virtual void _update_health_bar() = 0;
		virtual ProgressBar* _get_health_bar() = 0;
		virtual void _stop_animations() = 0;
		virtual float _get_special_time() = 0;
		virtual void _set_special_time(float value) = 0;
		virtual void _stop_special() = 0;
		virtual void _start_special() = 0;
		virtual bool _get_safe_mode() = 0;
		virtual IPlayer* _clone() = 0;
		virtual float _get_speed() = 0;
		virtual void _set_was_revived(bool value) = 0;
		virtual void _heal() = 0;
		virtual std::map<String, String> _get_controll_buttons() = 0;
		virtual void _set_controll_buttons(String move_up, String move_down, String move_left, String move_right, String fight_up, 
			String fight_down, String fight_left, String fight_right, String special) = 0;
		virtual void _set_is_attacking(bool value) = 0;
	};
}
