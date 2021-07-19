#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class CurrentRoom;

	class Enemies
	{
		static Enemies* list;

		std::vector<Node2D*> enemies;
		bool is_spawning = false;
		int enemy_to_spawn_count = 0;

		int size;

		Enemies();

	public:
		static Enemies* get_singleton()
		{
			if (list == nullptr)
				list = new Enemies;

			return list;
		}

		void _change_start_parameters();
		int _get_enemies_count();
		void _add_enemy(Node2D* enemy);
		void _remove_enemy(Node2D* enemy);
		void _remove_player1();
		void _remove_player2();
		void _set_player1(Node* player);
		void _set_player2(Node* player);
		void _clear();
		bool spawning();
		void set_spawning(bool value);
		int get_enemy_to_spawn_count();
		void set_enemy_to_spawn_count(int count);
		void _set_enemy_count(int count);
	};
}