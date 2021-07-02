#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

PlayersContainer* PlayersContainer::object = nullptr;

PlayersContainer::PlayersContainer()
{
	player1 = nullptr;
	player2 = nullptr;
}

void godot::PlayersContainer::_clear()
{
	player1 = nullptr;
	player2 = nullptr;
}

void PlayersContainer::_set_player1(Node2D* player1)
{
	this->player1 = player1;

	if (player1 != nullptr)
		main_camera = player1->get_node("/root/Node2D/Node/Camera2D");

	//game over
	if (player1 == nullptr && player2 == nullptr)
	{
		ResourceLoader* rld = ResourceLoader::get_singleton();
		Ref<PackedScene> game_over_screen = rld->load("res://Assets/Prefabs/Scenes/GameOver.tscn");
		main_camera->add_child(game_over_screen->instance());
		main_camera->get_tree()->set_pause(true);
	}
}

void PlayersContainer::_set_player2(Node2D* player2)
{
	this->player2 = player2;

	if (player2 != nullptr)
		main_camera = player2->get_node("/root/Node2D/Node/Camera2D");

	//game over
	if (player1 == nullptr && player2 == nullptr)
	{
		ResourceLoader* rld = ResourceLoader::get_singleton();
		Ref<PackedScene> game_over_screen = rld->load("res://Assets/Prefabs/Scenes/GameOver.tscn");
		main_camera->add_child(game_over_screen->instance());
		main_camera->get_tree()->set_pause(true);
	}
}

void godot::PlayersContainer::_set_player1_regular(Node2D* player1)
{
	player1_regular = player1;
}

void godot::PlayersContainer::_set_player2_regular(Node2D* player2)
{
	player2_regular = player2;
}

Node2D* godot::PlayersContainer::_get_player1_regular()
{
	return player1_regular;
}

Node2D* godot::PlayersContainer::_get_player2_regular()
{
	return player2_regular;
}

Node2D* godot::PlayersContainer::_get_player1()
{
	return player1;
}

Node2D* godot::PlayersContainer::_get_player2()
{
	return player2;
}

int godot::PlayersContainer::_players_count()
{
	int player_count = 0;
	player_count += player1 != nullptr;
	player_count += player2 != nullptr;
	return player_count;
}

void godot::PlayersContainer::_add_key(String key_type)
{
	key_list.push_back(key_type);
}

Array godot::PlayersContainer::_get_key_list()
{
	return key_list;
}

void godot::PlayersContainer::_clear_keys()
{
	key_list.clear();
}
