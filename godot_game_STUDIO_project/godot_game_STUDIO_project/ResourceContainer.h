#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class ResourceContainer
	{
	private:
		static ResourceContainer* object;

		String _player1_fight;
		String _player2_fight;
		String _player_died;
		String _enemy_take_damage;
		String _player_take_damage;
		String _player_revive;
		String _open_door;
		String _stone_action;
		String _collect_key;
		String _collect_bad_item;
		String _collect_good_item;
		String _show_next_level;
		String _shield;
		String _game_over;
		String _player_to_ghost;
		String _dash;
		String _egg_destroy;
		String _egg_spawn;
		String _slime_jump;
		String _slime_action;
		String _target_hit;
		String _target_crack;

		ResourceContainer();
	public:
		static ResourceContainer* _get_instance()
		{
			if (object == nullptr)
				object = new ResourceContainer;

			return object;
		}
		String player1_fight();
		String player2_fight();
		String player_died();
		String enemy_take_damage();
		String player_take_damage();
		String player_revive();
		String open_door();
		String stone_action();
		String collect_key();
		String collect_bad_item();
		String collect_good_item();
		String show_next_level();
		String shield();
		String game_over();
		String player_to_ghost();
		String dash();
		String egg_destroy();
		String egg_spawn();
		String slime_jump();
		String slime_action();
		String target_hit();
		String target_crack();
	};
}