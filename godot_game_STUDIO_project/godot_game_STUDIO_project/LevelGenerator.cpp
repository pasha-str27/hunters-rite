#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::LevelGenerator::LevelGenerator()
{
}

godot::LevelGenerator::~LevelGenerator()
{
	positions.clear();

	rooms.clear();
}

void godot::LevelGenerator::_register_methods()
{
	register_method("_init", &LevelGenerator::_init);
	register_method("_ready", &LevelGenerator::_ready);
	register_method("_get_next_room", &LevelGenerator::_get_next_room);	

	register_property<LevelGenerator, int>("map_size", &LevelGenerator::map_size, -1);
	register_property<LevelGenerator, Ref<PackedScene>>("room", &LevelGenerator::room, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("down_door", &LevelGenerator::down_door, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("up_door", &LevelGenerator::up_door, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("right_door", &LevelGenerator::right_door, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("left_door", &LevelGenerator::left_door, nullptr);

	register_property<LevelGenerator, int>("wall_top_count", &LevelGenerator::wall_top_count, 0);
	register_property<LevelGenerator, int>("floor_count", &LevelGenerator::floor_count, 0);
	register_property<LevelGenerator, int>("stone_count", &LevelGenerator::stone_count, 0);
	register_property<LevelGenerator, int>("spike_count", &LevelGenerator::spike_count, 0);
	register_property<LevelGenerator, int>("roof_count", &LevelGenerator::roof_count, 0);
}

void godot::LevelGenerator::_init()
{
}

void godot::LevelGenerator::_ready()
{
	_generate();
	_buid_roofs();
	_buid_doors();
	_buid_floors();
	_buid_top_wall();

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();
	int rand_value;

	for (int i = 1; i < rooms.size(); ++i)
	{
		rand_value = rng->randi_range(0, 1);
		if (rand_value == 0)
		{
			_buid_stones_first_step(rooms[i]);
			rand_value = rng->randi_range(0, 2);

			if(rand_value > 0)
				_buid_spikes_second_step(rooms[i]);

			continue;
		}

		if (rand_value == 1)
		{
			_buid_spikes_first_step(rooms[i]);
			rand_value = rng->randi_range(0, 2);

			if (rand_value > 0)
				_buid_stones_second_step(rooms[i]);

		}
	}

	CameraController::current_room = rooms[0];
}

void godot::LevelGenerator::_connect_rooms(Node2D* prev, Node2D* next, Vector2 dir)
{
	prev->call("_set_adjacent_room", dir, next);
	next->call("_set_adjacent_room", -dir, prev);
	/*
	prev->call("_set_num_of_adjacent_rooms", (int)prev->call("_get_num_of_adjacent_rooms") + 1);
	next->call("_set_num_of_adjacent_rooms", (int)next->call("_get_num_of_adjacent_rooms") + 1);*/
}

void godot::LevelGenerator::_generate()
{
	positions.push_back(Vector2(0, 0));
	rooms.push_back(cast_to<Node2D>(room->instance()));

	add_child(rooms[0]);

	size++;

	Vector2 new_room_position = Vector2::ZERO + Vector2(0, step_y);
	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[0], rooms[rooms.size() - 1], Vector2(0, 1));
	}

	size++;

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
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
				{
					_buid_room(new_room_position);
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(1, 0));
				}

				break;
			}
			case 1:
			{
				Vector2 new_room_position = i + Vector2(-step_x, 0);
				if (!_has_room(positions, new_room_position))
				{
					_buid_room(new_room_position);
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(-1, 0));
				}

				break;	
			}
			case 2:
			{
				Vector2 new_room_position = i + Vector2(0, step_y);
				if (!_has_room(positions, new_room_position))
				{
					_buid_room(new_room_position);
					_connect_rooms(rooms[index],rooms[rooms.size() - 1], Vector2(0, 1));
				}

				break;
			}
			case 3:
			{
				Vector2 new_room_position = i + Vector2(0, -step_y);
				if (!_has_room(positions, new_room_position))
				{
					_buid_room(new_room_position);
					_connect_rooms(rooms[index], rooms[rooms.size() - 1], Vector2(0, -1));
				}

				break;
			}
			default:
				break;
			}

			if (size > map_size)
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
	size++;
	node = nullptr;
}

void godot::LevelGenerator::_buid_doors()
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2(0, 1)))
			rooms[i]->add_child(down_door->instance());

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2(0, -1)))
			rooms[i]->add_child(up_door->instance());

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2(1, 0)))
			rooms[i]->add_child(right_door->instance());

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2(-1, 0)))
			rooms[i]->add_child(left_door->instance());
	}	
}

void godot::LevelGenerator::_buid_roofs()
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader *loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();
	for (auto room : rooms)
		if (random->randi_range(0, 5) >= 1)
		{
			prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/WallTops/roof" + String::num(random->randi_range(1, roof_count)) + ".tscn"));
			room->add_child(prefab->instance());
		}
	loader = nullptr;
}

void godot::LevelGenerator::_buid_floors()
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();
	for (int i = 1; i<rooms.size(); ++i)
	{
		prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Floor/floor" + String::num(random->randi_range(1, floor_count)) + ".tscn"));
		rooms[i]->add_child(prefab->instance());
	}
	loader = nullptr;
	prefab = nullptr;
}

void godot::LevelGenerator::_buid_top_wall()
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();
	for (auto room : rooms)
		if (random->randi_range(0, 5) >= 1)
		{
			prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Walls/wall" + String::num(random->randi_range(1, wall_top_count)) + ".tscn"));
			room->add_child(prefab->instance());
		}
	loader = nullptr;
}

void godot::LevelGenerator::_buid_stones_first_step(Node2D* room)
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();
	prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Stones/stone" + String::num(random->randi_range(1, spike_count)) + ".tscn"));
	TileMap* tile_map = cast_to<TileMap>(prefab->instance());
	room->add_child(tile_map);

	auto arr = tile_map->get_used_cells();

	for (int i = 0; i < arr.size(); ++i)
	{
		Vector2 pos = (Vector2)arr[i];
		room->call("_set_cell_value", pos.y + 8, pos.x + 14, 2);
	}	

	prefab = nullptr;
	loader = nullptr;
	tile_map = nullptr;
}

void godot::LevelGenerator::_buid_stones_second_step(Node2D* room)
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();

	TileMap* tile_map=nullptr;

	for (int k = 0; k < 4; ++k)
	{
		prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Stones/stone" + String::num(random->randi_range(1, spike_count)) + ".tscn"));
		tile_map = cast_to<TileMap>(prefab->instance());
		room->add_child(tile_map);

		auto arr = tile_map->get_used_cells();

		bool check_res = true;


		for (int i = 0; i < arr.size(); ++i)
		{
			Vector2 pos = (Vector2)arr[i];
			if ((int)room->call("_get_cell_value", pos.y + 8, pos.x + 14) != 0)		
			{
				check_res = false;
				tile_map->queue_free();
				break;
			}
		}

		if (check_res)
		{
			for (int i = 0; i < arr.size(); ++i)
			{
				Vector2 pos = (Vector2)arr[i];
				room->call("_set_cell_value", pos.y + 8, pos.x + 14, 2);
			}
			break;
		}
	}


	prefab = nullptr;
	loader = nullptr;
	tile_map = nullptr;
}

void godot::LevelGenerator::_buid_spikes_first_step(Node2D* room)
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();
	prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Spikes/spike" + String::num(random->randi_range(1, spike_count)) + ".tscn"));
	
	TileMap* tile_map = cast_to<TileMap>(prefab->instance());
	room->add_child(tile_map);

	auto arr = tile_map->get_used_cells();

	for (int i = 0; i < arr.size(); ++i)
	{
		Vector2 pos = (Vector2)arr[i];

		//Godot::print(pos);
		room->call("_set_cell_value", pos.y + 8, pos.x + 14, 3);
	}
	prefab = nullptr;
	loader = nullptr;
	tile_map = nullptr;
}

void godot::LevelGenerator::_buid_spikes_second_step(Node2D* room)
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();

	TileMap* tile_map;

	for (int k = 0; k < 4; ++k)
	{
		prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Spikes/spike" + String::num(random->randi_range(1, spike_count)) + ".tscn"));
		tile_map = cast_to<TileMap>(prefab->instance());
		room->add_child(tile_map);

		auto arr = tile_map->get_used_cells();

		bool check_res = true;
		for (int i = 0; i < arr.size(); ++i)
		{
			Vector2 pos = (Vector2)arr[i];
			if ((int)room->call("_get_cell_value", pos.y + 8, pos.x + 14) != 0)
			{
				check_res = false;
				tile_map->queue_free();
				break;
			}
		}

		if (check_res)
		{
			for (int i = 0; i < arr.size(); ++i)
			{
				Vector2 pos = (Vector2)arr[i];
				room->call("_set_cell_value", pos.y + 8, pos.x + 14, 3);
			}
			break;
		}
	}


	prefab = nullptr;
	loader = nullptr;
	tile_map = nullptr;
}

Node2D* godot::LevelGenerator::_get_next_room(Vector2 current_room_position)
{
	int index = 0;
	for(auto i : positions)
	{
		if (i == current_room_position)
			break;

		index++;
	}

	return rooms[index];
}
