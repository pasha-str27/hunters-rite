#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

EnemyAIContext::EnemyAIContext()
{
	strategy = nullptr;
}

EnemyAIContext::~EnemyAIContext()
{
	if(strategy!=nullptr)
		delete strategy;
	strategy = nullptr;
}


void EnemyAIContext::_set_strategy(IEnemyAI* strategy)
{
	this->strategy = strategy;
}

void EnemyAIContext::_process(float delta)
{
	strategy->_process(delta);
}

void godot::EnemyAIContext::set_enemy(Node2D* enemy)
{
	strategy->_set_enemy(enemy);
}

void godot::EnemyAIContext::set_player1(Node2D* player1)
{
	strategy->_set_player1(player1);
}

void godot::EnemyAIContext::set_player2(Node2D* player2)
{
	strategy->_set_player2(player2);
}

Node2D* godot::EnemyAIContext::get_player1()
{
	return strategy->_get_player1();
}

Node2D* godot::EnemyAIContext::get_player2()
{
	return strategy->_get_player2();
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
	strategy->_delete_player1();
}

void godot::EnemyAIContext::_delete_player2()
{
	strategy->_delete_player2();
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

void godot::EnemyAIContext::_change_dir()
{
	strategy->_change_dir();
}

void godot::EnemyAIContext::_set_is_player1_onArea(bool value)
{
	strategy->_set_is_player1_onArea(value);
}

void godot::EnemyAIContext::_set_is_player2_onArea(bool value)
{
	strategy->_set_is_player2_onArea(value);
}

void godot::EnemyAIContext::_change_start_parameters()
{
	strategy->_change_start_parameters();
}
