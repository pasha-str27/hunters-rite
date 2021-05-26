#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::LevelGenerator::LevelGenerator()
{
}

void godot::LevelGenerator::_register_methods()
{
	register_method("_init", &LevelGenerator::_init);
	register_method("_ready", &LevelGenerator::_ready);

	register_property<LevelGenerator, int>("map_size", &LevelGenerator::map_size, -1);
	register_property<LevelGenerator, Ref<PackedScene>>("room", &LevelGenerator::room, nullptr);
}

void godot::LevelGenerator::_init()
{
}

void godot::LevelGenerator::_ready()
{
	_generate();
}

void godot::LevelGenerator::_connect_rooms(Node2D* prev, Node2D* next, Vector2 dir)
{
	prev->call("_set_adjacent_room", dir, next);
	next->call("_set_adjacent_room", dir, prev);
	
	prev->call("_set_num_of_adjacent_rooms", (int)prev->call("_get_num_of_adjacent_rooms") + 1);
	next->call("_set_num_of_adjacent_rooms", (int)next->call("_get_num_of_adjacent_rooms") + 1);
}

void godot::LevelGenerator::_generate()
{
	positions.push_back(Vector2(0, 0));
	rooms.push_back(cast_to<Node2D>(room->instance()));

	add_child(rooms[0]);

	size++;

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();

	while (size < map_size)
	{
		int index = 0;
		std::vector<Vector2> old_positions(positions);
		for (auto i : old_positions)
		{
			int direction = int(rng->randi_range(0, 3));
			switch (direction)
			{
			case 0:
			{
				Vector2 new_room_position = i + Vector2(step_x, 0);
				if (!_has_room(positions, new_room_position))
					_buid_room(new_room_position);

				if ((bool)rooms[index]->call("_adjacent_room_is_null", Vector2(1, 0)))
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(1, 0));

				break;
			}
			case 1:
			{
				Vector2 new_room_position = i + Vector2(-step_x, 0);
				if (!_has_room(positions, new_room_position)) 
					_buid_room(new_room_position);

				if ((bool)rooms[index]->call("_adjacent_room_is_null", Vector2(-1, 0)))
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(-1, 0));

				break;	
			}
			case 2:
			{
				Vector2 new_room_position = i + Vector2(0, step_y);
				if (!_has_room(positions, new_room_position))
					_buid_room(new_room_position);

				if ((bool)rooms[index]->call("_adjacent_room_is_null", Vector2(0, 1)))
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(0, 1));

				break;
			}
			case 3:
			{
				Vector2 new_room_position = i + Vector2(0, -step_y);
				if (!_has_room(positions, new_room_position))
					_buid_room(new_room_position);

				if ((bool)rooms[index]->call("_adjacent_room_is_null", Vector2(0, -1)))
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(0, -1));

				break;
			}
			default:
				break;
			}

			if (size >= map_size)
				return;

			++index;
		}
	}
}

bool godot::LevelGenerator::_has_room(std::vector<Vector2> positions, Vector2 pos)
{
	for (auto node : positions)
		if (pos == node)
			return true;

	return false;
}

void godot::LevelGenerator::_buid_room(Vector2 pos)
{
	Node2D* node = cast_to<Node2D>(room->instance());
	node->set_global_position(pos);
	rooms.push_back(node);
	positions.push_back(pos);
	add_child(node);
	size += 1;
}
