#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class IEnemyAI;
	class ISlimeAttackState;

	class EnemyAIContext
	{
		IEnemyAI* strategy;

	public:
		EnemyAIContext();
		~EnemyAIContext();
		void _set_strategy(IEnemyAI* strategy);
		IEnemyAI* _get_strategy();
		void _process(float  delta);
		void set_enemy(Node2D* enemy);
		void set_player1(Node2D* player1);
		void set_player2(Node2D* player2);
		Node2D* get_player1();
		Node2D* get_player2();
		void _add_bullet(Node* bullet);
		void change_can_fight(bool value);
		void change_can_fight(bool value, ISlimeAttackState* state);
		void _delete_player1();
		void _delete_player2();
		void _change_dir_after_time();
		String _get_current_player();
		void _set_speed(float value);
		void _change_dir();
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		void _change_start_parameters();
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
	};
}