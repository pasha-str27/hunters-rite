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
}

godot::Room::Room()
{
	adjacent_rooms.insert(std::make_pair(Vector2(1, 0), nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2(-1, 0), nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2(0, 1), nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2(0, -1), nullptr));

	std::vector<int> tmp_vector;
	for (int i = 0; i < 3; ++i)
	{
		tmp_vector.clear();
		for (int j = 0; j < 28; ++j)
			tmp_vector.push_back(1);
		room_map.push_back(tmp_vector);
	}

	for (int i = 3; i < 16; ++i)
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
}

void godot::Room::_init()
{
}

bool godot::Room::_is_empty_pos(int i, int j)
{
	return !room_map[i][j];
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
