#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SpiderAI : public EnemyData, public KinematicBody2D
	{
		std::vector<Node2D*> bullets;
		int max_bullet_count;
		bool can_move;
		std::vector<int> directions;

		Vector2 dir;
		bool is_cheking;
		float speed;
		Vector2 old_pos;

	public:
		SpiderAI(Ref<PackedScene>& bullet, Node2D* node);
		void _process(float delta);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void reset_directions();
		void change_direction();
		void _remove_side(int side);
		void _change_dir_after_time();
		void _fight(Node2D *player1, Node2D* player2);
		void _set_speed(float value);
	};
}
