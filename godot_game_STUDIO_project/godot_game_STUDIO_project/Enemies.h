#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Enemies
	{
		static Enemies* list;

		std::vector<Node2D*> enemies;

		Enemies();

	public:
		static Enemies* get_singleton()
		{
			if (list == nullptr)
				list = new Enemies;

			return list;
		}

		int _get_enemies_count();

		void _add_enemy(Node2D* enemy);

		void _remove_enemy(Node2D* enemy);

		void _remove_player1();
		void _remove_player2();
		void _set_player1(Node* player);
		void _set_player2(Node* player);
		void _clear();
	};
}