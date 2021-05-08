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
		float dir;
		float speed;
		bool can_move;

	public:
		StatueMeleeAI(Ref<PackedScene>& bullet, Node2D* node, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _process(float delta);
		void change_can_fight(bool value);
		//void _fight(Node2D* player1, Node2D* player2);
		void _set_speed(float value);
	};
}