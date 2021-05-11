#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BatAI : public EnemyData, public KinematicBody2D
	{
		//Node2D* enemy;
		//Node2D* player1;
		//Node2D* player2;
		Node2D* current_goal;
		bool can_move;

		Vector2 dir;
		bool is_cheking;
		String current_player;
		float speed;

	public:
		BatAI(Ref<PackedScene>& bullet, Node2D* node, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _process(float delta);
		void change_can_fight(bool value);
		void _fight(Node2D* player1, Node2D* player2);
		void _delete_player1();
		void _delete_player2();
		String _get_current_player();
		void _set_speed(float value);
	};
}