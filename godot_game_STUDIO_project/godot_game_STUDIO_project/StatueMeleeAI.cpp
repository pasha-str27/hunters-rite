#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::StatueMeleeAI::StatueMeleeAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2):
	EnemyData(node_tmp, nullptr, nullptr)
{
	min_scale = 1;
	max_scale = 10;
	current_scale = min_scale;
	dir = 1;
	speed = 5;
	damage = 20;
	can_fight = true;
}

void godot::StatueMeleeAI::change_can_fight(bool value)
{
	can_fight = value;
}

void godot::StatueMeleeAI::_fight(Node2D* player1, Node2D* player2)
{
	can_fight = false;
	_get_enemy()->call("_start_timer");

	if (player1 != nullptr)
		player1->call("_take_damage", damage, false);

	if (player2 != nullptr)
		player2->call("_take_damage", damage, false);
}

void godot::StatueMeleeAI::_set_speed(float value)
{
	speed = value;
}

void godot::StatueMeleeAI::_set_player1(Node2D* player1)
{
	EnemyData::_set_player1(player1);
	player1->call("_take_damage", damage, false);
}

void godot::StatueMeleeAI::_set_player2(Node2D* player2)
{
	EnemyData::_set_player2(player2);
	player2->call("_take_damage", damage, false);
}

void godot::StatueMeleeAI::_delete_player1()
{
	EnemyData::_delete_player1();

	if (_get_player1() == nullptr && _get_player2() == nullptr)
		can_fight = false;
}

void godot::StatueMeleeAI::_delete_player2()
{
	EnemyData::_delete_player2();

	if (_get_player1() == nullptr && _get_player2() == nullptr)
		can_fight = false;
}

void godot::StatueMeleeAI::_process(float delta)
{
	if (!(current_scale <= max_scale && current_scale >= min_scale))
		dir *= -1;

	current_scale += dir * delta;
	cast_to<Area2D>(_get_enemy()->get_child(3))->set_scale(Vector2(current_scale, current_scale));

	if(can_fight)
		_fight(_get_player1(), _get_player2());
}