#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::InputReviveManager::~InputReviveManager()
{
}

void godot::InputReviveManager::_set_player_buttons(Dictionary input_map)
{
	this->input_map = input_map;
	_generate_new_key();
}

void godot::InputReviveManager::_generate_new_key()
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	random->randomize();
	current_key = input_map.keys()[random->randi_range(0, 3)];
}

String godot::InputReviveManager::_get_current_key()
{
	return current_key;
}

String godot::InputReviveManager::_get_current_value()
{
	return input_map[current_key];
}
