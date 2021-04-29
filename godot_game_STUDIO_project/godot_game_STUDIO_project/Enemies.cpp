#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

godot::Enemies* godot::Enemies::list = nullptr;

godot::Enemies::Enemies()
{
}

void godot::Enemies::_add_enemy(Node2D* enemy)
{
	enemies.push_back(enemy);
}

void godot::Enemies::_remove_enemy(Node2D* enemy)
{
	for (int i = 0; i < enemies.size(); ++i)
		if (enemies[i] == enemy)
		{
			//enemies.erase(enemies.begin() + i, enemies.begin() + i + 1);
			enemies.erase(enemies.begin() + i, enemies.end());
			return;
		}
}

void godot::Enemies::_remove_player1()
{
	for (auto node : enemies)
		node->call("_remove_player1");
}

void godot::Enemies::_remove_player2()
{
	for (auto node : enemies)
		node->call("_remove_player2");
}