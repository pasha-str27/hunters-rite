#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::StatueMeleeAI::StatueMeleeAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2):
	EnemyData(node_tmp, player1, player2)
{
	min_scale = 1;
	max_scale = 8;
	current_scale = min_scale;
	dir = 1;
	speed = 5;
	can_move = true;
}

void godot::StatueMeleeAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::StatueMeleeAI::_set_speed(float value)
{
	speed = value;
}

void godot::StatueMeleeAI::_process(float delta)
{
	if (can_move)
	{
		if (!(current_scale <= max_scale && current_scale >= min_scale))
			dir *= -1;

		current_scale += dir * delta;
		cast_to<Area2D>(_get_enemy()->get_child(3))->set_scale(Vector2(current_scale, current_scale));
	}
}