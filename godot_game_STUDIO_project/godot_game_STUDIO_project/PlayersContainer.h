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
		Node2D* player1_regular;
		Node2D* player2_regular;
		Node* main_camera;
		Array key_list = {};
		PlayersContainer();

	public:
		static PlayersContainer* _get_instance()
		{
			if (object == nullptr)
				object = new PlayersContainer;

			return object;
		}

		void _clear();
		void _set_player1(Node2D* player1);
		void _set_player2(Node2D* player2);
		void _set_player1_regular(Node2D* player1);
		void _set_player2_regular(Node2D* player2);
		//	never nullptr (in coop)
		Node2D* _get_player1_regular();
		Node2D* _get_player2_regular();
		//	nullptr when die or ghost
		Node2D* _get_player1();
		Node2D* _get_player2();
		int _players_count();
		void _add_key(String key_type);
		Array _get_key_list();
		void _clear_keys();
		void _show_game_over_screen();
	};
}