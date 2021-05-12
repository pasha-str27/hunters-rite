#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayersContainer
	{
		static PlayersContainer* object;

		Node2D* player1;
		Node2D* player2;
		PlayersContainer();

	public:
		static PlayersContainer* _get_instance()
		{
			if (object == nullptr)
				object = new PlayersContainer;

			return object;
		}

		void _set_player1(Node2D* player1);
		void _set_player2(Node2D* player2);
		Node2D* _get_player1();
		Node2D* _get_player2();
		int _players_count();
	};
}