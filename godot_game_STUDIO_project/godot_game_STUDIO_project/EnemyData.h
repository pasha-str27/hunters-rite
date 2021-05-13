#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class EnemyData : public IEnemyAI
	{
		Node2D* enemy;

	public:
		EnemyData(Node2D* enemy);
		~EnemyData();
		void _add_bullet(Node* bullet = nullptr);
		void _remove_side(int side);
		void _change_dir_after_time();
		void _delete_player1();
		void _delete_player2();
		String _get_current_player();
		void _fight(Node2D* player1, Node2D* player2);
		Node2D* _get_enemy();
		void _set_enemy(Node2D* enemy);
		void _set_player1(Node2D* player1 = nullptr);
		void _set_player2(Node2D* player2 = nullptr);
		Node2D* _get_player1();
		Node2D* _get_player2();
	};
}