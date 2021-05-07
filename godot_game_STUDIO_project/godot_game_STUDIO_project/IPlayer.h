#include <Godot.hpp>
#include <Node.hpp>

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
	};
}
