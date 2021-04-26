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
	delete strategy;
	delete enemy;
	delete player1;
	delete player2;
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
