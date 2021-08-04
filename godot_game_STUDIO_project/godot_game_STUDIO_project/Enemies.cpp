#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Enemies* godot::Enemies::list = nullptr;

godot::Enemies::Enemies()
{
}

void godot::Enemies::_change_start_parameters()
{
	for (auto enemy : enemies)
		enemy->call("_change_start_parameters");
}

int godot::Enemies::_get_enemies_count()
{
	if (MenuButtons::game_type == TUTORIAL)
		return size;

	return enemies.size();
}

void godot::Enemies::_add_enemy(Node2D* enemy)
{
	enemies.push_back(enemy);
}

void godot::Enemies::_remove_enemy(Node2D* enemy)
{
	if(enemy->has_method("_remove_taken_positions"))
		enemy->call("_remove_taken_positions");

	for (int i = 0; i < enemies.size(); ++i)
		if (enemies[i] == enemy)
		{
			enemies.erase(enemies.begin() + i, enemies.begin() + i + 1);

			if (enemies.size() == 0)
			{
				auto cur_room = CurrentRoom::get_singleton()->_get_current_room();
				CustomExtensions::GetChildByName(cur_room->get_node("/root/Node2D/Node"), "Camera2D")->call("_open_doors");

				for (int i = cur_room->get_child_count() - 1; i >= 0; --i)
					if (cur_room->get_child(i)->get_name().find("fill_door") != -1)
						cur_room->get_child(i)->queue_free();
				cur_room->call("_set_were_here", true);
			}

			return;
		}

	if ((String)CurrentRoom::get_singleton()->_get_current_room()->call("_get_room_type") == "boss_room" && enemies.size() == 0)
	{
		Ref<PackedScene> exit_prefab = nullptr;
		exit_prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/exit.tscn");
		Node2D *exit_node = Node::cast_to<Node2D>(exit_prefab->instance());
		CurrentRoom::get_singleton()->_get_current_room()->add_child(exit_node);
	}
}

void godot::Enemies::_remove_player1()
{
	for (Node2D* node : enemies)
	{
		if (node->is_in_group("statue_melee"))
			node->get_node("MagnitZone")->call("_set_player1");

		node->call_deferred("_remove_player1");
	}

	PlayersContainer::_get_instance()->_set_player1(nullptr);
}

void godot::Enemies::_remove_player2()
{
	for (Node2D* node : enemies)
	{
		if (node->is_in_group("statue_melee"))
			node->get_node("MagnitZone")->call("_set_player2");

		node->call("_remove_player2");
	}

	PlayersContainer::_get_instance()->_set_player2(nullptr);
}

void godot::Enemies::_set_player1(Node* player)
{
	for (auto node : enemies)
		node->call("_set_player1", player);
}

void godot::Enemies::_set_player2(Node* player)
{
	for (auto node : enemies)
		node->call("_set_player2", player);
}

void godot::Enemies::_clear()
{
	is_spawning = false;
	enemies.clear();
	size = 0;
}

bool godot::Enemies::spawning()
{
	return is_spawning;
}

void godot::Enemies::set_spawning(bool value)
{
	is_spawning = value;
}

int godot::Enemies::get_enemy_to_spawn_count()
{
	return enemy_to_spawn_count;
}

void  godot::Enemies::set_enemy_to_spawn_count(int count)
{
	enemy_to_spawn_count = count;
}

void godot::Enemies::_set_enemy_count(int count)
{
	size = count;
}
