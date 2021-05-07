#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class StatueMeleeAI : public IEnemyAI, public KinematicBody2D
	{
		Node2D* enemy;
		float min_scale;
		float max_scale;
		float current_scale;
		float dir;
		float speed;

	public:
		StatueMeleeAI(Ref<PackedScene>& bullet, Node2D* node, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _process(float delta, Node2D* enemy = nullptr, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void reset_directions();
		void change_direction();
		void _remove_side(int side);
		void _change_dir_after_time();
		void _fight(Node2D* player1, Node2D* player2);
		void _delete_player1(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _delete_player2(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		String _get_current_player();
		void _set_speed(float value);
	};
}