#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
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
	};
}