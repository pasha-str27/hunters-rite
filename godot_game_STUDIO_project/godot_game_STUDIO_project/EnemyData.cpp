#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

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
	//PlayersContainer::_get_instance()->_set_player1(player1);
}

void godot::EnemyData::_set_player2(Node2D* player2)
{
	//PlayersContainer::_get_instance()->_set_player2(player2);
}

Node2D* godot::EnemyData::_get_player1()
{
	return PlayersContainer::_get_instance()->_get_player1();
}

Node2D* godot::EnemyData::_get_player2()
{
	return PlayersContainer::_get_instance()->_get_player2();
}

godot::EnemyData::EnemyData(Node2D* enemy)
{
	this->enemy = enemy;
}

godot::EnemyData::~EnemyData()
{
}

void godot::EnemyData::_add_bullet(Node* bullet)
{
}

void godot::EnemyData::_remove_side(int side)
{
}

void godot::EnemyData::_change_dir_after_time()
{
}

void godot::EnemyData::_delete_player1()
{
	//PlayersContainer::_get_instance()->_set_player1(nullptr);
}

void godot::EnemyData::_delete_player2()
{
	//PlayersContainer::_get_instance()->_set_player2(nullptr);
}

String godot::EnemyData::_get_current_player()
{
	return String();
}

void godot::EnemyData::_fight(Node2D* player1, Node2D* player2)
{
}
