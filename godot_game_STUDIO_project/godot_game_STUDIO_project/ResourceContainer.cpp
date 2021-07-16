#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

ResourceContainer* ResourceContainer::object = nullptr;

ResourceContainer::ResourceContainer() 
{
	String link = "res://Assets/Prefabs/SoundsEffects/Effects/";
	_player1_fight = link + "Player1Fight.tscn";
	_player2_fight = link + "Player2Fight.tscn";
	_player_died = link + "PlayerDied.tscn";
	_enemy_take_damage = link + "EnemyTakeDamage.tscn";
	_player_take_damage = link + "PlayerTakeDamage.tscn";
	_player_revive = link + "PlayerRevive.tscn";
	_open_door = link + "OpenDoors.tscn";
	_stone_action = link + "StoneAction.tscn";
	_collect_key = link + "CollectKey.tscn";
	_collect_bad_item = link + "TakeBadItem.tscn";
	_collect_good_item = link + "TakeGoodItem.tscn";
	_show_next_level = link + "ShowNextLevel.tscn";
	_shield = link + "Shield.tscn";
	_game_over = link + "GameOver.tscn";
	_player_to_ghost = link + "PlayerToGhost.tscn";
	_dash = link + "Dash.tscn";
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

String godot::ResourceContainer::stone_action()
{
	return _stone_action;
}

String godot::ResourceContainer::collect_key()
{
	return _collect_key;
}

String godot::ResourceContainer::collect_bad_item()
{
	return _collect_bad_item;
}

String godot::ResourceContainer::collect_good_item()
{
	return _collect_good_item;
}

String godot::ResourceContainer::show_next_level()
{
	return _show_next_level;
}

String godot::ResourceContainer::shield()
{
	return _shield;
}

String godot::ResourceContainer::game_over()
{
	return _game_over;
}

String godot::ResourceContainer::player_to_ghost()
{
	return _player_to_ghost;
}

String godot::ResourceContainer::dash()
{
	return _dash;
}

