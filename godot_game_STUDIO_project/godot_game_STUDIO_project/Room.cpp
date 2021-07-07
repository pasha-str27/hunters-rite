#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

bool godot::Room::_adjacent_room_is_null(Vector2 pos)
{
	return adjacent_rooms[pos] == nullptr;
}

void godot::Room::_register_methods()
{
	register_method("_init", &Room::_init);
	register_method("_ready", &Room::_ready);
	register_method("_adjacent_room_is_null", &Room::_adjacent_room_is_null);
	register_method("_set_num_of_adjacent_rooms", &Room::_set_num_of_adjacent_rooms);
	register_method("_get_num_of_adjacent_rooms", &Room::_get_num_of_adjacent_rooms);
	register_method("_set_adjacent_room", &Room::_set_adjacent_room);
	register_method("_is_empty_pos", &Room::_is_empty_pos);
	register_method("_set_cell_value", &Room::_set_cell_value);
	register_method("_get_cell_value", &Room::_get_cell_value);
	register_method("print", &Room::print);
	register_method("_fill_empty_positions", &Room::_fill_empty_positions);
	register_method("_add_list", &Room::_add_list);
	register_method("_get_list_of_keys", &Room::_get_list_of_keys);
	register_method("_get_room_difficulty", &Room::_get_room_difficulty);
	register_method("_get_room_type", &Room::_get_room_type);
	register_method("_set_room_type", &Room::_set_room_type);
	register_method("_get_were_here", &Room::_get_were_here);
	register_method("_set_were_here", &Room::_set_were_here);
	register_method("_set_is_special", &Room::_set_is_special);
	register_method("_get_is_special", &Room::_get_is_special);
	register_method("_get_enemy_spawn_positions", &Room::_get_enemy_spawn_positions);
	register_method("_add_new_enemy", &Room::_add_new_enemy);
	register_method("_spawn_enemy", &Room::_spawn_enemy);
	register_method("_clear_enemy_to_spawn", &Room::_clear_enemy_to_spawn);
}

godot::Room::Room()
{
	adjacent_rooms.insert(std::make_pair(Vector2::RIGHT, nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2::LEFT, nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2::DOWN, nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2::UP, nullptr));

	std::vector<int> tmp_vector;
	for (int i = 0; i < 4; ++i)
	{
		tmp_vector.clear();
		for (int j = 0; j < 28; ++j)
			tmp_vector.push_back(1);
		room_map.push_back(tmp_vector);
	}

	for (int i = 3; i < 15; ++i)
	{
		tmp_vector.clear();
		tmp_vector.push_back(1);
		for (int j = 1; j < 27; ++j)
			tmp_vector.push_back(0);
		tmp_vector.push_back(1);
		room_map.push_back(tmp_vector);
	}	

	tmp_vector.clear();
	for (int j = 0; j < 28; ++j)
		tmp_vector.push_back(1);
	room_map.push_back(tmp_vector);
}

godot::Room::~Room()
{
	for (auto row : room_map)
		row.clear();
	room_map.clear();
	empty_pos_world_coordinates.clear();
	adjacent_rooms.clear();
}

void godot::Room::_init()
{
}

bool godot::Room::_is_empty_pos(int i, int j)
{
	return !room_map[i][j];
}

int godot::Room::_get_cell_value(int i, int j)
{
	return room_map[i][j];
}

void godot::Room::_set_cell_value(int i, int j, int value)
{
	room_map[i][j] = value;
}

void godot::Room::_fill_empty_positions(Node2D* room)
{
	for (int i=3;i<room_map.size()-1;++i)
		for (int j=1; j<room_map[i].size()-1;++j)
			if (room_map[i][j] == 0)
			{
				empty_pos_world_coordinates.push_back((Vector2(j, i) * 32 
					+ room->get_global_position()
					- Vector2(896, 544) / 2 + Vector2(16, 16)));
			}			
}

void godot::Room::print()
{
	for (int i = 0; i < room_map.size(); ++i)
	{
		String tmp = "";
		for (int j = 0; j < room_map[i].size(); ++j)
			tmp += String::num(room_map[i][j]);
		Godot::print(tmp);
	}
}

void godot::Room::_add_list(Array list)
{	
	Array lst = ((String)list[0]).split(", ");
	for (int i = 0; i < lst.size(); ++i)
		list_of_keys.push_back(lst[i]);
	//list_of_keys.push_back(list);
}

Array godot::Room::_get_list_of_keys()
{
	return list_of_keys;
}

float godot::Room::_get_room_difficulty()
{
	return room_difficulty;
}

String godot::Room::_get_room_type()
{
	return room_type;
}

void godot::Room::_set_room_type(String type)
{
	room_type = type;
}

bool godot::Room::_get_were_here()
{
	return were_here;
}

void godot::Room::_set_were_here(bool value)
{
	were_here = value;
}

void godot::Room::_set_is_special(bool value)
{
	is_special = value;
}

bool godot::Room::_get_is_special()
{
	return is_special;
}

Array godot::Room::_get_enemy_spawn_positions()
{
	Array arr = {};
	Array poses = {};

	for (auto pos : empty_pos_world_coordinates)
		poses.push_back(pos);

	arr.push_back(poses);
	return arr;
}

void godot::Room::_add_new_enemy(Node2D* enemy, Vector2 position)
{
	Timer* timer = Timer::_new();
	add_child(timer);
	enemies_to_spawn.push_back({ enemy, position, timer });
	Array index = {};
	index.push_back(enemies_to_spawn.size() - 1);
	timer->connect("timeout", this, "_spawn_enemy", index);
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();
	timer->start(rng->randf_range(0.1f, 1.0f));

}

void godot::Room::_spawn_enemy(int number)
{
	add_child(enemies_to_spawn[number].enemy);
	enemies_to_spawn[number].enemy->set_global_position(enemies_to_spawn[number].new_pos);
	enemies_to_spawn[number].timer->queue_free();

	if (!enemies_to_spawn[number].enemy->has_method("_change_start_parameters"))
	{
		for (int i = 0; i < enemies_to_spawn[number].enemy->get_child_count(); ++i)
			if (enemies_to_spawn[number].enemy->get_child(i)->has_method("_change_start_parameters"))
			{
				enemies_to_spawn[number].enemy->get_child(i)->call("_change_start_parameters");
				return;
			}
	}

	enemies_to_spawn[number].enemy->call_deferred("_change_start_parameters");
}

void godot::Room::_clear_enemy_to_spawn()
{
	enemies_to_spawn.clear();
}

void godot::Room::_set_num_of_adjacent_rooms(int value)
{
	num_of_adjacent_rooms = value;
}

void godot::Room::_set_adjacent_room(Vector2 pos, Node2D* value)
{
	adjacent_rooms[pos] = value;
}

int godot::Room::_get_num_of_adjacent_rooms()
{
	return num_of_adjacent_rooms;
}

void godot::Room::_ready()
{
}
