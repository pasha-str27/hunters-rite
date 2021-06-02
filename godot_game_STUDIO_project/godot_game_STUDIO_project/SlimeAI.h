#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SlimeAI : public EnemyData, public KinematicBody2D
	{
		bool can_move;
		std::vector<int> directions;

		Vector2 dir;
		bool is_cheking;
		float speed;
		float damage = 33;
		bool is_player1_onArea = false;
		bool is_player2_onArea = false;

		bool was_setted = false;

		Vector2 old_pos;

	public:
		SlimeAI(Ref<PackedScene>& bullet, Node2D* node);
		~SlimeAI();
		void _process(float delta);
		void change_can_fight(bool value);
		void reset_directions();
		void change_direction();
		void _remove_side(int side);
		void _change_dir_after_time();
		void _fight(Node2D* player1, Node2D* player2);
		Vector2 directions_swich(int value);
		void _set_speed(float value);
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
	};
}