#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BatAI : public EnemyData, public KinematicBody2D
	{
		Node2D* current_goal;
		bool can_move;

		Vector2 dir;
		String current_player;

	public:
		BatAI(Ref<PackedScene>& bullet, Node2D* node);
		~BatAI();
		void _process(float delta);
		void change_can_fight(bool value);
		void _delete_player1();
		void _delete_player2();
		String _get_current_player();
		void _change_dir();
	};
}