#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::TutotialGenerator::TutotialGenerator()
{
}

godot::TutotialGenerator::~TutotialGenerator()
{
	positions.clear();

	rooms.clear();
}

void godot::TutotialGenerator::_register_methods()
{
	register_method("_init", &TutotialGenerator::_init);
	register_method("_ready", &TutotialGenerator::_ready);
	register_method("_get_next_room", &TutotialGenerator::_get_next_room);
	register_method("_get_keys_count", &TutotialGenerator::_get_keys_count);
	register_method("_clear", &TutotialGenerator::_clear);
	register_method("_get_rooms", &TutotialGenerator::_get_rooms);
	register_method("_get_rooms_positions", &TutotialGenerator::_get_rooms_positions);
	
	register_property<TutotialGenerator, Ref<PackedScene>>("room", &TutotialGenerator::room, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("down_door", &TutotialGenerator::down_door, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("up_door", &TutotialGenerator::up_door, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("right_door", &TutotialGenerator::right_door, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("left_door", &TutotialGenerator::left_door, nullptr);

	register_property<TutotialGenerator, Ref<PackedScene>>("down_door_fill", &TutotialGenerator::down_door_fill, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("up_door_fill", &TutotialGenerator::up_door_fill, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("right_door_fill", &TutotialGenerator::right_door_fill, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("left_door_fill", &TutotialGenerator::left_door_fill, nullptr);

	register_property<TutotialGenerator, int>("wall_top_count", &TutotialGenerator::wall_top_count, 0);
	register_property<TutotialGenerator, int>("roof_count", &TutotialGenerator::roof_count, 0);

	register_property<TutotialGenerator, Ref<PackedScene>>("jertovnik", &TutotialGenerator::jertovnik, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("key_room_pedestal", &TutotialGenerator::key_room_pedestal, nullptr);

	register_property<TutotialGenerator, Array>("keys_prefabs", &TutotialGenerator::keys_prefabs, {});

	register_property<TutotialGenerator, Ref<PackedScene>>("big_stone", &TutotialGenerator::big_stone, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("lock_sprite", &TutotialGenerator::lock_sprite, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("sword_item", &TutotialGenerator::sword_item, nullptr);
	register_property<TutotialGenerator, Ref<PackedScene>>("task_item", &TutotialGenerator::task_item, nullptr);
}

void godot::TutotialGenerator::_init()
{
}

void godot::TutotialGenerator::_ready()
{
	_clear();
	keys_prefabs_local = keys_prefabs.duplicate();

	_generate();
	_buid_doors();

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();
	int rand_value;

	_spawn_big_stone();

	CurrentRoom::get_singleton()->_set_current_room(rooms[0]);

	for(auto node : rooms)
		node->call("_fill_empty_positions", node);

	////create key holders
	get_node("/root/Node2D/Node/Camera2D")->call("_get_type_keys");

	_set_keys(rooms[rooms.size() - 2], generated_keys);

	if (generated_colors_keys.size() > 0)
		rooms[rooms.size() - 2]->call("_set_last_key_color", generated_colors_keys[generated_colors_keys.size() - 1]);

	_buid_roofs();
	_buid_top_wall();
	_build_locks();
	_build_fill_doors();
	get_node("/root/Node2D/Node/Camera2D/MiniMap")->call_deferred("_start_treking");
}

void godot::TutotialGenerator::_connect_rooms(Node2D* prev, Node2D* next, Vector2 dir)
{
	prev->call("_set_adjacent_room", dir, next);
	next->call("_set_adjacent_room", -dir, prev);

	prev->call("_set_num_of_adjacent_rooms", (int)prev->call("_get_num_of_adjacent_rooms") + 1);
	next->call("_set_num_of_adjacent_rooms", (int)next->call("_get_num_of_adjacent_rooms") + 1);
}

void godot::TutotialGenerator::_generate()
{
	Vector2 new_room_position = Vector2(0, 0);

	positions.push_back(new_room_position);
	rooms.push_back(cast_to<Node2D>(room->instance()));

	add_child(rooms[0]);

	rooms[0]->call("_set_room_type", "tutorial");
	rooms[0]->call("_set_were_here", true);

	size++;

	new_room_position += Vector2(0, step_y);
	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[0], rooms[rooms.size() - 1], Vector2::DOWN);
		rooms[rooms.size() - 1]->call("_set_room_type", "tut_room");
	}

	new_room_position += Vector2(0, step_y);
	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[rooms.size() - 2], rooms[rooms.size() - 1], Vector2::DOWN);
		rooms[rooms.size() - 1]->call("_set_room_type", "heal_room");
	}
	
	new_room_position += Vector2(0, step_y);
	if (MenuButtons::game_mode==COOP && !_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[rooms.size() - 2], rooms[rooms.size() - 1], Vector2::DOWN);
		rooms[rooms.size() - 1]->call("_set_room_type", "revive_room");
	}

	new_room_position = Vector2(0, step_y);
	new_room_position += Vector2(step_x, 0);

	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[1], rooms[rooms.size() - 1], Vector2::RIGHT);
		rooms[rooms.size() - 1]->call("_set_room_type", "atack_room");
	}

	new_room_position += Vector2(step_x, 0);

	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[rooms.size() - 2], rooms[rooms.size() - 1], Vector2::RIGHT);
		rooms[rooms.size() - 1]->call("_set_room_type", "game_room");
	}

	new_room_position = Vector2(0, step_y);
	new_room_position -= Vector2(step_x, 0);

	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[1], rooms[rooms.size() - 1], Vector2::LEFT);
		_generate_key(rooms[rooms.size() - 1]);
	}

	new_room_position -= Vector2(step_x, 0);

	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[rooms.size() - 2], rooms[rooms.size() - 1], Vector2::LEFT);
		_create_item_room(rooms[rooms.size() - 1]);
	}


	new_room_position = Vector2(0, -step_y);

	if (!_has_room(positions, new_room_position))
	{
		_buid_room(new_room_position);
		_connect_rooms(rooms[0], rooms[rooms.size() - 1], Vector2::UP);
		rooms[rooms.size() - 1]->call("_set_room_type", "boss_room");
	}
}

bool godot::TutotialGenerator::_has_room(std::vector<Vector2> positions, Vector2 pos)
{
	for (auto node : positions)
		if (pos == node)
			return true;

	return false;
}

Node2D* godot::TutotialGenerator::_buid_room(Vector2 pos)
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

void godot::TutotialGenerator::_buid_doors()
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::DOWN))
			rooms[i]->add_child(down_door->instance());

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::UP))
			rooms[i]->add_child(up_door->instance());

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::RIGHT))
			rooms[i]->add_child(right_door->instance());

		if (!(bool)rooms[i]->call("_adjacent_room_is_null", Vector2::LEFT))
			rooms[i]->add_child(left_door->instance());
	}
}

void godot::TutotialGenerator::_build_doors(int start_index, int end_index)
{
	for (int i = start_index; i < end_index; ++i)
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

void godot::TutotialGenerator::_buid_roofs()
{
	Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
	ResourceLoader* loader = ResourceLoader::get_singleton();
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

void godot::TutotialGenerator::_buid_top_wall()
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

Node2D* godot::TutotialGenerator::_get_next_room(Vector2 current_room_position)
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

void godot::TutotialGenerator::_create_item_room(Node2D* room)
{
	room->call("_set_is_special", true);
	room->call("_set_room_type", "item_room");

	auto spawned_jertovnik = cast_to<Node2D>(jertovnik->instance());
	add_child(spawned_jertovnik);
	spawned_jertovnik->set_global_position(room->get_global_position());

	auto item_points = get_parent()->get_node("Camera2D/EnemySpawner/ItemPoints");

	Vector2 left_item = cast_to<Node2D>(item_points->get_child(0))->get_position();
	Vector2 right_item = cast_to<Node2D>(item_points->get_child(1))->get_position();

	auto items_container = get_parent()->get_node("ItemsContainer");

	auto items = get_node("/root/Node2D/Items");

	Node2D* sword_item_node = cast_to<Node2D>(sword_item->instance());
	Node2D* task_item_node = cast_to<Node2D>(task_item->instance());

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();

	if (rng->randi_range(0, 1))
	{
		sword_item_node->set_global_position(room->get_global_position() + left_item);
		task_item_node->set_global_position(room->get_global_position() + right_item);
	}
	else
	{
		sword_item_node->set_global_position(room->get_global_position() + right_item);
		task_item_node->set_global_position(room->get_global_position() + left_item);
	}

	items->add_child(sword_item_node);
	items->add_child(task_item_node);
}

void godot::TutotialGenerator::_generate_key(Node2D* room)
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

void godot::TutotialGenerator::_set_keys(Node2D* room, Array t_keys)
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

void godot::TutotialGenerator::_spawn_big_stone()
{
	Node* room = rooms[2];

	auto stone = cast_to<Node2D>(big_stone->instance());
	room->add_child(stone);

	stone->set_global_position(stone->get_global_position() + Vector2(16, 2));
	stone->call("_change_start_parameters");

	room->call("_set_room_type", "heal_room");
	room->call("_set_is_special", true);
}

int godot::TutotialGenerator::_get_keys_count()
{
	return generated_keys.size();
}

void godot::TutotialGenerator::_clear()
{
	for (int i = 0; i < this->get_child_count(); i++)
		this->get_child(i)-> queue_free();

	this->positions.clear();
	this->rooms.clear();
	this->generated_keys.clear();
	generated_colors_keys.clear();
	size = 0;
}

Array godot::TutotialGenerator::_get_rooms()
{
	Array wrapper = {};
	for (auto room : rooms)
		wrapper.push_back(room);

	Array arr = {};
	arr.push_back(wrapper);
	return arr;
}

Array godot::TutotialGenerator::_get_rooms_positions()
{
	Array wrapper = {};
	for (auto pos : positions)
		wrapper.push_back(pos);

	Array arr = {};
	arr.push_back(wrapper);
	return arr;
}

void godot::TutotialGenerator::_build_locks()
{
	Vector2 dir;
	String door_name;
	int step = 30;

	for (int i = 0; i < rooms.size(); ++i)
	{
		dir = Vector2::DOWN;
		door_name = "DownDoor";

		_build_locks_in_room(rooms[i], dir, door_name, step);

		dir = Vector2::UP;
		door_name = "UpDoor";
		step = 23;

		_build_locks_in_room(rooms[i], dir, door_name, step);

		dir = Vector2::LEFT;
		step = 21;
		door_name = "LeftDoor";

		_build_locks_in_room(rooms[i], dir, door_name, step);

		dir = Vector2::RIGHT;
		door_name = "RightDoor";

		_build_locks_in_room(rooms[i], dir, door_name, step);
	}
}

void godot::TutotialGenerator::_build_locks_in_room(Node2D* room, Vector2 door_dir, String door_name, int step)
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

void godot::TutotialGenerator::_build_fill_doors()
{
	for (int i = 1; i < rooms.size(); ++i)
	{
		String room_type = rooms[i]->call("_get_room_type");
		if (room_type == "boos_room" || room_type == "game_room" || room_type == "mob_room")
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
