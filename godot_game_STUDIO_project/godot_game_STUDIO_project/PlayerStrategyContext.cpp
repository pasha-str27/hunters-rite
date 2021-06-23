#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::PlayerStrategyContext::_set_controll_buttons(String move_up, String move_down, String move_left, String move_right, String fight_up, String fight_down, String fight_left, String fight_right, String special)
{
	strategy->_set_controll_buttons(move_up, move_down, move_left, move_right, fight_up, fight_down, fight_left, fight_right, special);
}

bool godot::PlayerStrategyContext::_was_revived()
{
	return strategy->_was_revived();
}

float godot::PlayerStrategyContext::_get_max_HP()
{
	return strategy->_get_max_HP();
}

void godot::PlayerStrategyContext::_set_max_HP(float value)
{
	strategy->_set_max_HP(value);
}

void godot::PlayerStrategyContext::_update_health_bar()
{
	strategy->_update_health_bar();
}

ProgressBar* godot::PlayerStrategyContext::_get_health_bar()
{
	return strategy->_get_health_bar();
}

void godot::PlayerStrategyContext::_stop_animations()
{
	strategy->_stop_animations();
}

float godot::PlayerStrategyContext::_get_special_time()
{
	return strategy->_get_special_time();
}

void godot::PlayerStrategyContext::_set_special_time(float value)
{
	strategy->_set_special_time(value);
}

void godot::PlayerStrategyContext::_stop_special()
{
	strategy->_stop_special();
}

void godot::PlayerStrategyContext::_start_special()
{
	strategy->_start_special();
}

bool godot::PlayerStrategyContext::_get_safe_mode()
{
	return strategy->_get_safe_mode();
}

IPlayer* godot::PlayerStrategyContext::_clone()
{
	return strategy->_clone();
}

void godot::PlayerStrategyContext::_set_was_revived(bool value)
{
	strategy->_set_was_revived(value);
}

void godot::PlayerStrategyContext::_heal()
{
	strategy->_heal();
}

godot::PlayerStrategyContext::PlayerStrategyContext()
{
	strategy = nullptr;
}

godot::PlayerStrategyContext::~PlayerStrategyContext()
{
	strategy = nullptr;
}

void godot::PlayerStrategyContext::_set_strategy(IPlayer* strategy)
{
	this->strategy = strategy;
}

void godot::PlayerStrategyContext::_process_input()
{
	strategy->_process_input();
}

void godot::PlayerStrategyContext::_move()
{
	strategy->_move();
}

void godot::PlayerStrategyContext::_set_speed(float speed)
{
	strategy->_set_speed(speed);
}

void godot::PlayerStrategyContext::_fight(Node* node)
{
	strategy->_fight(node);
}

void godot::PlayerStrategyContext::_add_bullet(Node* node)
{
	strategy->_add_bullet(node);
}

void godot::PlayerStrategyContext::_change_can_fight(bool value)
{
	strategy->_change_can_fight(value);
}

bool godot::PlayerStrategyContext::_can_fight()
{
	return strategy->_can_fight();
}

void godot::PlayerStrategyContext::_set_enemy(Node* enemy)
{
	strategy->_set_enemy(enemy);
}

void godot::PlayerStrategyContext::_take_damage(float damage, bool is_spike)
{
	strategy->_take_damage(damage, is_spike);
}

float godot::PlayerStrategyContext::_get_HP()
{
	return strategy->_get_HP();
}

void godot::PlayerStrategyContext::_set_HP(float HP)
{
	strategy->_set_HP(HP);
}

float godot::PlayerStrategyContext::_get_damage()
{
	return strategy->_get_damage();
}

void godot::PlayerStrategyContext::_set_damage(float value)
{
	strategy->_set_damage(value);
}

void godot::PlayerStrategyContext::_revive()
{
	strategy->_revive();
}