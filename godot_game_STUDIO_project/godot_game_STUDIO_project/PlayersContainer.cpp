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

void PlayersContainer::_set_player1(Node2D* player1)
{
	this->player1 = player1;

	//game over
	if (player1 == nullptr && player2 == nullptr)
	{
		Godot::print("Game over");
	}
}

void PlayersContainer::_set_player2(Node2D* player2)
{
	this->player2 = player2;

	//game over
	if (player1 == nullptr && player2 == nullptr)
	{
		Godot::print("Game over");
	}
}

Node2D* godot::PlayersContainer::_get_player1()
{
	//if (player1 == nullptr)
	//	Godot::print("player1 is null");
	return player1;
}

Node2D* godot::PlayersContainer::_get_player2()
{
	//if (player2 == nullptr)
	//	Godot::print("player2 is null");
	return player2;
}

int godot::PlayersContainer::_players_count()
{
	int player_count = 0;
	player_count += player1 != nullptr;
	player_count += player2 != nullptr;
	return player_count;
}
