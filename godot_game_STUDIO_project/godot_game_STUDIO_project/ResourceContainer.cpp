#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

ResourceContainer* ResourceContainer::object = nullptr;

ResourceContainer::ResourceContainer() {
	_player1_fight = "res://Assets/Prefabs/SoundsEffects/Effects/Player1Fight.tscn";
	_player2_fight = "res://Assets/Prefabs/SoundsEffects/Effects/Player2Fight.tscn";
	_player_died = "res://Assets/Prefabs/SoundsEffects/Effects/PlayerDied.tscn";
	_enemy_take_damage = "res://Assets/Prefabs/SoundsEffects/Effects/EnemyTakeDamage.tscn";
	_player_take_damage = "res://Assets/Prefabs/SoundsEffects/Effects/PlayerTakeDamage.tscn";
	_player_revive = "res://Assets/Prefabs/SoundsEffects/Effects/PlayerRevive.tscn";
	_open_door = "res://Assets/Prefabs/SoundsEffects/Effects/OpenDoors.tscn";
}

String godot::ResourceContainer::player1_fight()
{
	return _player1_fight;
}

String godot::ResourceContainer::player2_fight()
{
	return _player2_fight;
}

String godot::ResourceContainer::player_died()
{
	return _player_died;
}

String godot::ResourceContainer::enemy_take_damage()
{
	return _enemy_take_damage;
}

String godot::ResourceContainer::player_take_damage()
{
	return _player_take_damage;
}

String godot::ResourceContainer::player_revive()
{
	return _player_revive;
}

String godot::ResourceContainer::open_door()
{
	return _open_door;
}
