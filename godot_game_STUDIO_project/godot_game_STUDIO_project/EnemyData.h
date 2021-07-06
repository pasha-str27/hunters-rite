#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class IEnemyAI;

	class EnemyData : public IEnemyAI
	{
		Node2D* enemy;
		float distance = 32;

	public:
		std::vector<Vector2> directions;

		EnemyData(Node2D* enemy);
		~EnemyData();
		void _process(float delta);
		void _set_speed(float value);
		void _add_bullet(Node* bullet = nullptr);
		void _change_dir_after_time();
		void _delete_player1();
		void _delete_player2();
		String _get_current_player();
		void _fight(Node2D* player1, Node2D* player2);
		Node2D* _get_enemy();
		void _set_enemy(Node2D* enemy);
		void _set_player1(Node2D* player1 = nullptr);
		void _set_player2(Node2D* player2 = nullptr);
		void _change_dir();
		Node2D* _get_player1();
		Node2D* _get_player2();
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		void _change_start_parameters();
		void remove_vector_element(Vector2 element);
		void reset_directions();
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
		void _remove_taken_positions();
		void change_can_fight(bool value, ISlimeAttackState* state);
		float _get_distance();
		void _set_distance(float value);
		void _set_direction(Vector2 dir);
	};
}