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
}

godot::Room::Room()
{
	adjacent_rooms.insert(std::make_pair(Vector2(1, 0), nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2(-1, 0), nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2(0, 1), nullptr));
	adjacent_rooms.insert(std::make_pair(Vector2(0, -1), nullptr));
}

void godot::Room::_init()
{
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
