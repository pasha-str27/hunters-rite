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
}

void PlayersContainer::_set_player2(Node2D* player2)
{
	this->player2 = player2;
}

Node2D* godot::PlayersContainer::_get_player1()
{
	return player1;
}

Node2D* godot::PlayersContainer::_get_player2()
{
	return player2;
}
