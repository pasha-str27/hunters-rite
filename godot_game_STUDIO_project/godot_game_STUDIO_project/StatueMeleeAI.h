#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class StatueMeleeAI : public EnemyData, public KinematicBody2D
	{
		float min_scale;
		float max_scale;
		float current_scale;
		float damage;
		float dir;
		float speed;
		bool can_fight;
		Node2D* player1;
		Node2D* player2;
	public:
		StatueMeleeAI(Ref<PackedScene>& bullet, Node2D* node);
		~StatueMeleeAI();
		void _process(float delta);
		void change_can_fight(bool value);
		void _fight(Node2D* player1, Node2D* player2);
		void _set_speed(float value);
		void _delete_player1();
		void _delete_player2();
		void _set_player1(Node2D* player1);
		void _set_player2(Node2D* player2);
	};
}