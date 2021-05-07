#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::StatueMeleeAI::StatueMeleeAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2)
{
	min_scale = 1;
	max_scale = 8;
	current_scale = min_scale;
	dir = 1;
	speed = 5;
}

void godot::StatueMeleeAI::_add_bullet(Node* node)
{
}

void godot::StatueMeleeAI::change_can_fight(bool value)
{
}

void godot::StatueMeleeAI::reset_directions()
{
}

void godot::StatueMeleeAI::change_direction()
{
}

void godot::StatueMeleeAI::_remove_side(int dir)
{
}

void godot::StatueMeleeAI::_change_dir_after_time()
{
}

void godot::StatueMeleeAI::_fight(Node2D* player1, Node2D* player2)
{
}

void godot::StatueMeleeAI::_delete_player1(Node2D* player1, Node2D* player2)
{
}

void godot::StatueMeleeAI::_delete_player2(Node2D* player1, Node2D* player2)
{
}

String godot::StatueMeleeAI::_get_current_player()
{
	return String();
}

void godot::StatueMeleeAI::_set_speed(float value)
{
	speed = value;
}

void godot::StatueMeleeAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	if (!(current_scale <= max_scale && current_scale >= min_scale))
		dir *= -1;

	current_scale += dir * delta;
	cast_to<Area2D>(enemy->get_child(3))->set_scale(Vector2(current_scale, current_scale));
}