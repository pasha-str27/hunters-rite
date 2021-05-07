#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

EnemyAIContext::EnemyAIContext()
{
	strategy = nullptr;
	enemy = nullptr;
	player1 = nullptr;
	player2 = nullptr;
}

EnemyAIContext::~EnemyAIContext()
{
	//delete strategy;
	//delete enemy;
	//delete player1;
	//delete player2;
}


void EnemyAIContext::_set_strategy(IEnemyAI* strategy)
{
	this->strategy = strategy;
}

void EnemyAIContext::_process(float delta)
{
	strategy->_process(delta, enemy, player1, player2);
}

void godot::EnemyAIContext::set_enemy(Node2D* enemy)
{
	this->enemy = enemy;
}

void godot::EnemyAIContext::set_player1(Node2D* player1)
{
	this->player1 = player1;
}

void godot::EnemyAIContext::set_player2(Node2D* player2)
{
	this->player2 = player2;
}

Node2D* godot::EnemyAIContext::get_player1()
{
	return player1;
}

Node2D* godot::EnemyAIContext::get_player2()
{
	return player2;
}

void godot::EnemyAIContext::_add_bullet(Node* bullet)
{
	strategy->_add_bullet(bullet);
}

void godot::EnemyAIContext::change_can_fight(bool value)
{
	strategy->change_can_fight(value);
}

void godot::EnemyAIContext::_delete_player1()
{
	strategy->_delete_player1(player1, player2);
	player1 = nullptr;
}

void godot::EnemyAIContext::_delete_player2()
{
	strategy->_delete_player2(player1, player2);
	player2 = nullptr;
}

void godot::EnemyAIContext::_remove_side(int side)
{
	strategy->_remove_side(side);
}

void godot::EnemyAIContext::_change_dir_after_time()
{
	strategy->_change_dir_after_time();
}

String godot::EnemyAIContext::_get_current_player()
{
	return strategy->_get_current_player();
}

void godot::EnemyAIContext::_set_speed(float value)
{
	strategy->_set_speed(value);
}
