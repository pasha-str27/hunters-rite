#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::InputReviveManager::_set_player1_buttons()
{
	keys.push_back("Player1_up");
	keys.push_back("Player1_down");
	keys.push_back("Player1_right");
	keys.push_back("Player1_left");
	_generate_new_key();
	Godot::print("button:");
	Godot::print(current_key);
}

void godot::InputReviveManager::_set_player2_buttons()
{
	keys.push_back("Player2_up");
	keys.push_back("Player2_down");
	keys.push_back("Player2_right");
	keys.push_back("Player2_left");
	_generate_new_key();
	Godot::print("button:");
	Godot::print(current_key);
}

void godot::InputReviveManager::_generate_new_key()
{
	RandomNumberGenerator* random = RandomNumberGenerator::_new();
	random->randomize();
	current_key = keys[random->randi_range(0, keys.size()-1)];
}

String godot::InputReviveManager::_get_current_key()
{
	return current_key;
}
