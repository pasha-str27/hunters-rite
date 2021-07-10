#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::EnemyData::remove_vector_element(Vector2 element)
{
	for (int i = 0; i < directions.size(); ++i)
		if (directions[i] == element)
		{
			directions.erase(directions.begin() + i, directions.begin() + i + 1);
			return;
		}
}

void godot::EnemyData::reset_directions()
{
	_set_distance(32);
	directions.clear();
}

void godot::EnemyData::_set_player(Node2D* player)
{
}

void godot::EnemyData::_remove_player(Node2D* player)
{
}

void godot::EnemyData::_remove_taken_positions()
{

}

void godot::EnemyData::change_can_fight(bool value, ISlimeAttackState* state)
{
}

float godot::EnemyData::_get_distance()
{
	return distance;
}

void godot::EnemyData::_set_distance(float value)
{
	distance = value;
}

void godot::EnemyData::_set_direction(Vector2 dir)
{
}

void godot::EnemyData::change_can_fight(bool value)
{
}

Vector2 godot::EnemyData::_get_goal()
{
	return Vector2();
}

void godot::EnemyData::_set_goal(Vector2 goal)
{
}

Node2D* godot::EnemyData::_get_enemy()
{
	return enemy;
}

void godot::EnemyData::_set_enemy(Node2D* enemy)
{
	this->enemy = enemy;
}

void godot::EnemyData::_set_player1(Node2D* player1)
{
}

void godot::EnemyData::_set_player2(Node2D* player2)
{
}

void godot::EnemyData::_change_dir()
{
}


Node2D* godot::EnemyData::_get_player1()
{
	return PlayersContainer::_get_instance()->_get_player1();
}

Node2D* godot::EnemyData::_get_player2()
{
	return PlayersContainer::_get_instance()->_get_player2();
}

void godot::EnemyData::_set_is_player1_onArea(bool value)
{
}

void godot::EnemyData::_set_is_player2_onArea(bool value)
{
}

void godot::EnemyData::_change_start_parameters()
{
}

godot::EnemyData::EnemyData(Node2D* enemy)
{
	this->enemy = enemy;
}

godot::EnemyData::~EnemyData()
{
	enemy = nullptr;
}

void godot::EnemyData::_process(float delta)
{
}

void godot::EnemyData::_set_speed(float value)
{
}

void godot::EnemyData::_add_bullet(Node* bullet)
{
}

void godot::EnemyData::_change_dir_after_time()
{
}

void godot::EnemyData::_delete_player1()
{
}

void godot::EnemyData::_delete_player2()
{
}

String godot::EnemyData::_get_current_player()
{
	return String();
}

void godot::EnemyData::_fight(Node2D* player1, Node2D* player2)
{
}
