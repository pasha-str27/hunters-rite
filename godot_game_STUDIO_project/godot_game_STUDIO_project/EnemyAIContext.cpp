#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

EnemyAIContext::EnemyAIContext()
{
	strategy = nullptr;
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
	player1 = nullptr;
}

void godot::EnemyAIContext::_delete_player2()
{
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
