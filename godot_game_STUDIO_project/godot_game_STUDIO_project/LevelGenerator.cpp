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
	register_method("_get_keys_count", &LevelGenerator::_get_keys_count);
	register_method("_clear", &LevelGenerator::_clear);
	register_method("_get_rooms", &LevelGenerator::_get_rooms);
	register_method("_get_rooms_positions", &LevelGenerator::_get_rooms_positions);	
	
	register_property<LevelGenerator, int>("map_size", &LevelGenerator::map_size, -1);
	register_property<LevelGenerator, int>("keys_frequency", &LevelGenerator::keys_frequency, -1);
	register_property<LevelGenerator, Ref<PackedScene>>("room", &LevelGenerator::room, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("down_door", &LevelGenerator::down_door, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("up_door", &LevelGenerator::up_door, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("right_door", &LevelGenerator::right_door, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("left_door", &LevelGenerator::left_door, nullptr);

	register_property<LevelGenerator, Ref<PackedScene>>("down_door_fill", &LevelGenerator::down_door_fill, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("up_door_fill", &LevelGenerator::up_door_fill, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("right_door_fill", &LevelGenerator::right_door_fill, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("left_door_fill", &LevelGenerator::left_door_fill, nullptr);

	register_property<LevelGenerator, int>("wall_top_count", &LevelGenerator::wall_top_count, 0);
	register_property<LevelGenerator, int>("floor_count", &LevelGenerator::floor_count, 0);
	register_property<LevelGenerator, int>("stone_count", &LevelGenerator::stone_count, 0);
	register_property<LevelGenerator, int>("spike_count", &LevelGenerator::spike_count, 0);
	register_property<LevelGenerator, int>("roof_count", &LevelGenerator::roof_count, 0);

	register_property<LevelGenerator, Ref<PackedScene>>("jertovnik", &LevelGenerator::jertovnik, nullptr);
	register_property<LevelGenerator, Ref<PackedScene>>("key_room_pedestal", &LevelGenerator::key_room_pedestal, nullptr);

	register_property<LevelGenerator, Array>("keys_prefabs", &LevelGenerator::keys_prefabs, {});

	register_property<LevelGenerator, Ref<PackedScene>>("big_stone", &LevelGenerator::big_stone, nullptr);	
	register_property<LevelGenerator, Ref<PackedScene>>("lock_sprite", &LevelGenerator::lock_sprite, nullptr);
}

void godot::LevelGenerator::_init()
{
}

void godot::LevelGenerator::_ready()
{
	_clear();
	keys_prefabs_local = keys_prefabs.duplicate();

	_generate();
	_buid_doors();

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();
	int rand_value;

	_spawn_big_stone();

	for (int i = 1; i < rooms.size(); ++i)
	{
		rand_value = rng->randi_range(0, 3);

		if (rand_value >= 0 && rand_value <= 1)
		{
			_buid_stones(rooms[i]);
			if (rand_value == 0)
				_buid_spikes(rooms[i]);
		}
		else
		{
			_buid_spikes(rooms[i]);
			if (rand_value == 2)
				_buid_stones(rooms[i]);
		}
	}
	CurrentRoom::get_singleton()->_set_current_room(rooms[0]);
	std::vector<Node2D*> cornered_rooms = this->_get_corner_rooms();

	auto boss_room = _create_boss_room(cornered_rooms);
	_create_item_room(cornered_rooms);

	if (map_size / keys_frequency > cornered_rooms.size())
	{
		for (int i = 1; i < rooms.size(); i++)
			if ((int)rooms[i]->call("_get_num_of_adjacent_rooms") > 1 && (int)rooms[i]->call("_get_num_of_adjacent_rooms") < 4)
				cornered_rooms.push_back(rooms[i]);
	}

	std::vector<Node2D*> rebuild_doors = _create_keys_rooms(cornered_rooms);
	if (!rebuild_doors.empty())
	{
		_build_doors(rooms.size() - (map_size / keys_frequency), rooms.size());
		_rebuild_doors(rebuild_doors);
	}

	for(auto node : rooms)
		node->call("_fill_empty_positions", node);

	//create key holders
	get_node("/root/Node2D/Node/Camera2D")->call("_get_type_keys");

	_set_keys(boss_room, generated_keys);

	if (generated_colors_keys.size() > 0)
		boss_room->call("_set_last_key_color", generated_colors_keys[generated_colors_keys.size() - 1]);

	_buid_roofs();
	_buid_floors();
	_buid_top_wall();
	_build_locks();
	_build_fill_doors();
	//	call set positions
	get_node("/root/Node2D/Node/Camera2D/MiniMap")->call_deferred("_start_treking");
}

void godot::LevelGenerator::_connect_rooms(Node2D* prev, Node2D* next, Vector2 dir)
{
	prev->call("_set_adjacent_room", dir, next);
	next->call("_set_adjacent_room", -dir, prev);

	prev->call("_set_num_of_adjacent_rooms", (int)prev->call("_get_num_of_adjacent_rooms") + 1);
	next->call("_set_num_of_adjacent_rooms", (int)next->call("_get_num_of_adjacent_rooms") + 1);
}

void godot::LevelGenerator::_generate()
{
	positions.push_back(Vector2(0, 0));
	rooms.push_back(cast_to<Node2D>(room->instance()));

	add_child(rooms[0]);

	rooms[0]->call("_set_room_type", "tutorial");
	rooms[0]->call("_set_were_here", true);

	size++;

	Vector2 new_room_position = Vector2(0, step_y);
	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[0], rooms[rooms.size() - 1], Vector2(0, 1));
	}

	size++;

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	Vector2 new_room_position;

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
				new_room_position = i + Vector2(step_x, 0);
				_try_build_room(positions, new_room_position, Vector2::RIGHT, rooms[index]);
				break;
			}
			case 1:
			{
				new_room_position = i + Vector2(-step_x, 0);
				_try_build_room(positions, new_room_position, Vector2::LEFT, rooms[index]);
				break;
			}
			case 2:
			{
				new_room_position = i + Vector2(0, step_y);
				_try_build_room(positions, new_room_position, Vector2::DOWN, rooms[index]);
				break;
			}
			case 3:
			{
				new_room_position = i + Vector2(0, -step_y);
				_try_build_room(positions, new_room_position, Vector2::UP, rooms[index]);
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

Node2D* godot::LevelGenerator::_buid_room(Vector2 pos)
{
	Node2D* node = cast_to<Node2D>(room->instance());
	node->set_global_position(pos);
	rooms.push_back(node);
	positions.push_back(pos);
	add_child(node);
	node->call("_set_room_type", "game_room");
	size++;
	return node;
}

void godot::LevelGenerator::_buid_doors()
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::DOWN))
			rooms[i]->add_child(down_door->instance(), true);

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::UP))
			rooms[i]->add_child(up_door->instance(), true);

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::RIGHT))
			rooms[i]->add_child(right_door->instance(), true);

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::LEFT))
			rooms[i]->add_child(left_door->instance(), true);
	}
}

void godot::LevelGenerator::_build_doors(int start_index, int end_index)
{
	for (int i = start_index; i < end_index; ++i)
	{
		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::DOWN))
			rooms[i]->add_child(down_door->instance(), true);

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

void godot::LevelGenerator::_buid_floors()
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();
	for (int i = 0; i<rooms.size(); ++i)
	{
		prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Floor/floor" + String::num(random->randi_range(1, floor_count)) + ".tscn"));
		rooms[i]->add_child(prefab->instance());
	}
	loader = nullptr;
	prefab = nullptr;
}

void godot::LevelGenerator::_buid_stones(Node2D* room)
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();

	TileMap* tile_map=nullptr;

	for (int k = 0; k < 4; ++k)
	{
		prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Stones/stone" + String::num(random->randi_range(1, stone_count)) + ".tscn"));
		tile_map = cast_to<TileMap>(prefab->instance());
		room->add_child(tile_map);

		if (_analize_tilemap(tile_map, room))
			break;
	}


	prefab = nullptr;
	loader = nullptr;
	tile_map = nullptr;
}

void godot::LevelGenerator::_buid_spikes(Node2D* room)
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
	Ref<PackedScene> prefab = nullptr;
	random->randomize();

	TileMap* tile_map = nullptr;

	for (int k = 0; k < 4; ++k)
	{
		prefab = loader->load(NodePath("res://Assets/Prefabs/Rooms/Spikes/spike" + String::num(random->randi_range(1, spike_count)) + ".tscn"));
		tile_map = cast_to<TileMap>(prefab->instance());
		room->add_child(tile_map);

		if (_analize_tilemap(tile_map, room))
			break;
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

std::vector<Node2D*> godot::LevelGenerator::_get_corner_rooms()
{
	std::vector<Node2D*> cornered_rooms = {};

	for (int i = 1; i < rooms.size(); i++)
		if ((int)rooms[i]->call("_get_num_of_adjacent_rooms") == 1)
			cornered_rooms.push_back(rooms[i]);


	return cornered_rooms;
}

std::vector<Node2D*> godot::LevelGenerator::_create_keys_rooms(std::vector<Node2D*>& cornered_rooms)
{
	std::vector<Node2D*> rebuild_doors = {};

	//	calculate keys count
	int keys_count = map_size / keys_frequency;
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	for (int i = 0; i < keys_count;)
	{
		bool contains = false;

		int index = rng->randi_range(0, cornered_rooms.size() - 1);

		auto room_to_build = cornered_rooms[index];

		for (auto i : rebuild_doors)
		{
			if (i == room_to_build)
			{
				contains = true;
				break;
			}
		}

		if (!contains)
			rebuild_doors.push_back(room_to_build);

		int direction = int(rng->randi_range(0, 3));
		switch (direction)
		{
		case 0:
		{
			Vector2 new_room_position = room_to_build->get_global_position() + Vector2(step_x, 0);
			if (!_has_room(positions, new_room_position))
			{
				auto builded_room = _buid_room(new_room_position);
				_connect_rooms(room_to_build, rooms[rooms.size() - 1], Vector2(1, 0));

				_generate_key(builded_room);

				i++;
			}

			break;
		}
		case 1:
		{
			Vector2 new_room_position = room_to_build->get_global_position() + Vector2(-step_x, 0);
			if (!_has_room(positions, new_room_position))
			{
				auto builded_room = _buid_room(new_room_position);
				_connect_rooms(room_to_build, rooms[rooms.size() - 1], Vector2(-1, 0));

				_generate_key(builded_room);

				i++;
			}

			break;
		}
		case 2:
		{
			Vector2 new_room_position = room_to_build->get_global_position() + Vector2(0, step_y);
			if (!_has_room(positions, new_room_position))
			{
				auto builded_room = _buid_room(new_room_position);
				_connect_rooms(room_to_build, rooms[rooms.size() - 1], Vector2(0, 1));

				_generate_key(builded_room);

				i++;
			}

			break;
		}
		case 3:
		{
			Vector2 new_room_position = room_to_build->get_global_position() + Vector2(0, -step_y);
			if (!_has_room(positions, new_room_position))
			{
				auto builded_room = _buid_room(new_room_position);
				_connect_rooms(room_to_build, rooms[rooms.size() - 1], Vector2(0, -1));

				_generate_key(builded_room);
				i++;
			}

			break;
		}
		default:
			break;
		}
	}

	return rebuild_doors;
}

void godot::LevelGenerator::_rebuild_doors(std::vector<Node2D*> rooms)
{
	for (auto room : rooms)
	{
		std::vector<Node2D*> old_doors = CustomExtensions::GetChildrenByWordInName(room, "Door");
		for (auto door : old_doors)
			door->queue_free();

		if (!(bool)room->call("_adjacent_room_is_null", Vector2::DOWN))
			room->add_child(down_door->instance());

		if (!(bool)room->call("_adjacent_room_is_null", Vector2::UP))
			room->add_child(up_door->instance());

		if (!(bool)room->call("_adjacent_room_is_null", Vector2::RIGHT))
			room->add_child(right_door->instance());

		if (!(bool)room->call("_adjacent_room_is_null", Vector2::LEFT))
			room->add_child(left_door->instance());
	}
}

void godot::LevelGenerator::_rebuild_doors(Node2D* room)
{
	std::vector<Node2D*> old_doors = CustomExtensions::GetChildrenByWordInName(room, "Door");
	for (auto door : old_doors)
		door->queue_free();

	if (!(bool)room->call("_adjacent_room_is_null", Vector2::DOWN))
		room->add_child(down_door->instance());

	if (!(bool)room->call("_adjacent_room_is_null", Vector2::UP))
		room->add_child(up_door->instance());

	if (!(bool)room->call("_adjacent_room_is_null", Vector2::RIGHT))
		room->add_child(right_door->instance());

	if (!(bool)room->call("_adjacent_room_is_null", Vector2::LEFT))
		room->add_child(left_door->instance());
}

void godot::LevelGenerator::_create_item_room(std::vector<Node2D*>& cornered_rooms)
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	if (cornered_rooms.empty())
	{
		for (int i = 1; i < rooms.size(); i++)
			if ((int)rooms[i]->call("_get_num_of_adjacent_rooms") > 1 && (int)rooms[i]->call("_get_num_of_adjacent_rooms") < 4)
				cornered_rooms.push_back(rooms[i]);
	}

	int index = rng->randi_range(0, cornered_rooms.size() - 1);
	auto room_to_build = cornered_rooms[index];

	Node2D* builded_room = _generate_room_to(room_to_build);
	builded_room->call("_set_is_special", true);
	builded_room->call("_set_room_type", "item_room");

	_rebuild_doors(builded_room);
	_rebuild_doors(room_to_build);

	cornered_rooms.erase(cornered_rooms.begin() + index, cornered_rooms.begin() + index + 1);

	auto spawned_jertovnik = cast_to<Node2D>(jertovnik->instance());
	add_child(spawned_jertovnik);
	spawned_jertovnik->set_global_position(builded_room->get_global_position());

	auto item_points = get_parent()->get_node("Camera2D/EnemySpawner/ItemPoints");

	Vector2 left_item = cast_to<Node2D>(item_points->get_child(0))->get_position();
	Vector2 right_item = cast_to<Node2D>(item_points->get_child(1))->get_position();

	auto items_container = get_parent()->get_node("ItemsContainer");

	items_container->call("_spawn_random_item", builded_room->get_global_position() + left_item);
	items_container->call("_spawn_random_item", builded_room->get_global_position() + right_item);

}

Node2D* godot::LevelGenerator::_create_boss_room(std::vector<Node2D*>& cornered_rooms)
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	if (cornered_rooms.empty())
	{
		for (int i = 1; i < rooms.size(); i++)
			if ((int)rooms[i]->call("_get_num_of_adjacent_rooms") > 1 && (int)rooms[i]->call("_get_num_of_adjacent_rooms") < 4)
				cornered_rooms.push_back(rooms[i]);
	}

	int index = rng->randi_range(0, cornered_rooms.size() - 1);
	auto room_to_build = cornered_rooms[index];

	Node2D* builded_room = _generate_room_to(room_to_build);

	builded_room->call("_set_is_special", true);

	_rebuild_doors(builded_room);
	_rebuild_doors(room_to_build);

	cornered_rooms.erase(cornered_rooms.begin() + index, cornered_rooms.begin() + index + 1);

	builded_room->call("_set_room_type", "boss_room");
	builded_room->call("_set_is_last_room", true);

	return builded_room;
}

Node2D* godot::LevelGenerator::_generate_room_to(Node2D* room_to_build)
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	bool spawned = false;
	Vector2 new_room_position;

	while (!spawned)
	{
		int direction = int(rng->randi_range(0, 3));
		switch (direction)
		{
		case 0:
		{
			new_room_position = room_to_build->get_global_position() + Vector2(step_x, 0);
			spawned = _try_build_room(positions, new_room_position, Vector2::RIGHT, room_to_build);
			break;
		}
		case 1:
		{
			new_room_position = room_to_build->get_global_position() + Vector2(-step_x, 0);
			spawned = _try_build_room(positions, new_room_position, Vector2::LEFT, room_to_build);
			break;
		}
		case 2:
		{
			new_room_position = room_to_build->get_global_position() + Vector2(0, step_y);
			spawned = _try_build_room(positions, new_room_position, Vector2::DOWN, room_to_build);
			break;
		}
		case 3:
		{
			new_room_position = room_to_build->get_global_position() + Vector2(0, -step_y);
			spawned = _try_build_room(positions, new_room_position, Vector2::UP, room_to_build);
			break;
		}
		default:
			break;
		}
	}

	return rooms[rooms.size() - 1];
}

void godot::LevelGenerator::_generate_key(Node2D* room)
{
	Vector2 pos = room->get_global_position();
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	auto pedestal = cast_to<Node2D>(key_room_pedestal->instance());
	add_child(pedestal);
	pedestal->set_global_position(pos);
	pedestal->set_z_as_relative(false);
	pedestal->set_z_index(3);

	int key_index = rng->randi_range(0, keys_prefabs_local.size() - 1);
	Ref<PackedScene> key_prefab = keys_prefabs_local[key_index];
	auto key = cast_to<Node2D>(key_prefab->instance());
	add_child(key);
	key->set_global_position(pos);

	keys_prefabs_local.remove(key_index);

	if (!generated_keys.empty())
		_set_keys(room, generated_keys);

	room->call("_set_room_type", "key_room");
	room->call("_set_is_special", true);

	generated_keys.push_back(key->call("_get_type"));	
	generated_colors_keys.push_back(key->call("_get_color"));

	if (generated_colors_keys.size() > 1)
		room->call("_set_last_key_color", generated_colors_keys[generated_colors_keys.size() - 2]);
}

void godot::LevelGenerator::_set_keys(Node2D* room, Array t_keys)
{
	////	creating fucking wrapper for transferring array
	Array params = {};
	//	creating another stupid array for our array
	Array keys = {};
	//	pushing our data
	keys.push_back(t_keys);
	//	pushing stupid array to fucking wrapper
	params.push_back(keys);
	//	calling func
	room->call("_add_list", params);
}

void godot::LevelGenerator::_spawn_big_stone()
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	int rand = 0;

	Node* room = nullptr;

	do
	{
		rand = rng->randi_range(1, rooms.size() - 1);
		room = rooms[rand];
	} while ((bool)room->call("_get_is_special"));

	auto stone = cast_to<Node2D>(big_stone->instance());
	room->add_child(stone);

	stone->set_global_position(stone->get_global_position() + Vector2(16, 2));
	stone->call("_change_start_parameters");

	room->call("_set_room_type", "heal_room");
	room->call("_set_is_special", true);
}

int godot::LevelGenerator::_get_keys_count()
{
	return generated_keys.size();
}

void godot::LevelGenerator::_clear()
{
	for (int i = 0; i < this->get_child_count(); i++)
		this->get_child(i)-> queue_free();

	this->positions.clear();
	this->rooms.clear();
	this->generated_keys.clear();
	generated_colors_keys.clear();
	size = 0;

	if(GameManager::current_level > 1)
		map_size += 2;
}

Array godot::LevelGenerator::_get_rooms()
{
	Array wrapper = {};
	for (auto room : rooms)
		wrapper.push_back(room);

	Array arr = {};
	arr.push_back(wrapper);
	return arr;
}

Array godot::LevelGenerator::_get_rooms_positions()
{
	Array wrapper = {};
	for (auto pos : positions)
		wrapper.push_back(pos);

	Array arr = {};
	arr.push_back(wrapper);
	return arr;
}

void godot::LevelGenerator::_build_locks()
{
	Vector2 dir;
	String door_name;
	int step = 25;

	for (int i = 0; i < rooms.size(); ++i)
	{
		dir = Vector2::DOWN;
		door_name = "DownDoor";

		_build_locks_in_room(rooms[i], dir, door_name, step);

		dir = Vector2::UP;
		door_name = "UpDoor";
		step = 20;

		_build_locks_in_room(rooms[i], dir, door_name, step);

		dir = Vector2::LEFT;
		door_name = "LeftDoor";
		step = 21;

		_build_locks_in_room(rooms[i], dir, door_name, step);

		dir = Vector2::RIGHT;
		door_name = "RightDoor";

		_build_locks_in_room(rooms[i], dir, door_name, step);
	}
}

void godot::LevelGenerator::_build_locks_in_room(Node2D* room, Vector2 door_dir, String door_name, int step)
{
	Vector2 delta_step;

	if (door_dir == Vector2::UP)
		delta_step = -Vector2(0, 720);

	if (door_dir == Vector2::DOWN)
		delta_step = Vector2(0, 720);

	if (door_dir == Vector2::RIGHT)
		delta_step = Vector2(1024, 0);

	if (door_dir == Vector2::LEFT)
		delta_step = -Vector2(1024, 0);

	Vector2 next_room_pos = room->get_global_position() + delta_step;

	if (!(bool)room->call("_adjacent_room_is_null", door_dir))
		for (int j = 0; j < room->get_child_count(); ++j)
			if (room->get_child(j)->get_name().find(door_name) != -1)
			{
				auto next_room = _get_next_room(next_room_pos);

				if ((int)next_room->call("_get_key_count") > 0)
				{
					auto lock_node = lock_sprite->instance();
					room->get_child(j)->get_node("SpawnPoint")->add_child(lock_node);
					cast_to<Node2D>(lock_node)->set_position(door_dir * step);
					Color col = next_room->call("_get_last_key_color");
					cast_to<Sprite>(lock_node)->set_modulate(Color(col.r, col.g, col.b, 150.0/255.0));
				}
			}
}

void godot::LevelGenerator::_build_fill_doors()
{
	for (int i = 1; i < rooms.size(); ++i)
	{
		String room_type = rooms[i]->call("_get_room_type");
		if (room_type == "boss_room" || room_type == "game_room" || room_type == "mob_room")
		{
			if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::DOWN))
				rooms[i]->add_child(down_door_fill->instance(), true);

			if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::UP))
				rooms[i]->add_child(up_door_fill->instance(), true);

			if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::RIGHT))
				rooms[i]->add_child(right_door_fill->instance(), true);

			if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::LEFT))
				rooms[i]->add_child(left_door_fill->instance(), true);
		}
	}
}
