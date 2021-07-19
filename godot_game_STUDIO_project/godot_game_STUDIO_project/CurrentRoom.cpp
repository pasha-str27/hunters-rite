#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::CurrentRoom* godot::CurrentRoom::curr_room = nullptr;

void godot::CurrentRoom::_set_current_room(Node2D* room)
{
	cur_room_node = room;
}

Node2D* godot::CurrentRoom::_get_current_room()
{
	return cur_room_node;
}
