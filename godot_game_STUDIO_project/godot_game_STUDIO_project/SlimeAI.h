#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SlimeAI : public IEnemyAI, public KinematicBody2D
	{
		std::vector<Node2D*> bullets;
		int max_bullet_count;
		Node2D* enemy;
		bool can_move;
		std::vector<int> directions;

		Vector2 dir;
		bool is_cheking;

	public:
		SlimeAI(Ref<PackedScene>& bullet, Node2D* node);
		void _process(float delta, Node2D* enemy = nullptr, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void reset_directions();
		void change_direction();
		void _remove_side(int side);
		void _change_dir_after_time();
		void _fight(Node2D* player1, Node2D* player2);
		Vector2 directions_swich(int value);
	};
}