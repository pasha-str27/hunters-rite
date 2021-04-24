#include "Room.h"
#include <Node.hpp>

void godot::Room::Respawn()
{
	Godot::print("respawning...");
	if (possible_rooms.size() == 0) {
		Array new_possible_rooms = SetUpPossibleRooms();
		CustomExtensions::AddRange(possible_rooms, new_possible_rooms);
	}

	if (possible_rooms.size() == 0)
	{
		auto spawned_c_r = cast_to<Node2D>(generation->closed_room->instance());
		spawned_c_r->set_global_position(this->get_global_position());
		get_node("/root/Node2D/Rooms")->add_child(spawned_c_r, true);
		this->queue_free();
		return;
	}
	Godot::print("respawning...2");

	//  respawn to random room
	RandomNumberGenerator* randomizer = RandomNumberGenerator::_new();
	randomizer->randomize();
	int rand = randomizer->randi_range(0, possible_rooms.size() - 1);
	randomizer = nullptr;

	auto new_room = cast_to<Node2D>(cast_to<PackedScene>(possible_rooms[rand])->instance());
	//  delete from list spawned
	Godot::print("respawning...3");

	possible_rooms.remove(rand);
	new_room->call("_set_possible_rooms", possible_rooms, 1);
	new_room->set_global_position(this->get_global_position());
	get_node("/root/Node2D")->get_node("Rooms")->add_child(new_room, true);
	Godot::print("respawning...4");

	//  delete this room
	this->queue_free();
}

void godot::Room::_register_methods()
{
	register_method("_ready", &Room::_ready);
	register_method("_process", &Room::_process);
	register_method("_add_door_collision", &Room::_add_door_collision);
	register_method("_get_directions", &Room::_get_directions);
	register_method("_get_instance", &Room::_get_instance);	
	register_method("_set_possible_rooms", &Room::_set_possible_rooms);
	register_method("CheckClosedRoom", &Room::CheckClosedRoom);
	register_method("IsCorrectPlaced", &Room::IsCorrectPlaced);
	
	register_property<Room, Array>("doors", &Room::doors, {});
	register_property<Room, bool>("Is Start Room", &Room::start_room, false);
	register_property<Room, bool>("Is Closed Room", &Room::closed_room, false);
}

void godot::Room::_init()
{

}

void godot::Room::_ready()
{
	if (start_room)
		correct_placed = true;
	generation = get_node("/root/Node2D")->call("_get_instance");

	timer->connect("timeout", this, "IsCorrectPlaced");
	add_child(timer, true);
	timer->start(.5f);
}

void godot::Room::_process(float delta)
{
	if (need_to_spawn) {
		if (current != nullptr)
			current->SpawnRoom();
		current = nullptr;
		need_to_spawn = false;
	}
}

godot::Room* godot::Room::_get_instance()
{
	return this;
}

godot::Array godot::Room::_get_directions()
{
	return this->doors;
}

void godot::Room::_add_door_collision(String dir)
{
	door_collisions.push_back(dir);
	//possible_rooms = CustomExtensions::FindAll(possible_rooms, [dir](Node* node) {
	//	auto n = cast_to<Node2D>(cast_to<PackedScene>(node)->instance());
	//	Array arr = n->call("_get_directions");
	//	n = nullptr;
	//	Godot::print("respawning dirs count: " + String::num(arr.size()));
	//	return !arr.has(dir);
	//});
	if(correct_placed)
		Respawn();
}

void godot::Room::_set_possible_rooms(Array a)
{
	this->possible_rooms = a;
}

godot::Room::Room()
{
	timer = Timer::_new();
}

godot::Room::~Room()
{
	generation = nullptr;
	doors.clear();
}

godot::Array godot::Room::SetUpPossibleRooms()
{
	Array new_doors = CustomExtensions::FindAll(doors, [this](String x) {
		for (int i = 0; i < door_collisions.size(); i++)
		{
			if (x != door_collisions[i])
				continue;

			return false;
		}
		return true;
	});

	return CustomExtensions::FindAll(generation->GetListByDirections(new_doors), [this](Node* x) {
		auto xx = cast_to<Node2D>(cast_to<PackedScene>(x)->instance());
		Array dirs = xx->call("_get_directions");
		xx = nullptr;
		if (dirs.size() == 0)
			return true;

		for (int i = 0; i < door_collisions.size(); i++)
		{
			if (!dirs.has(door_collisions[i]))
				continue;

			return false;
		}
		return true;
	}
	);
}

void godot::Room::SpawnNeighborRooms()
{
	Array arr = CustomExtensions::GetComponentsInChildren(this, "Spawners");

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] != nullptr) {
			current = arr[i];
			current->SpawnRoom();
		}		
	}
}

void godot::Room::CheckClosedRoom()
{
	timer->disconnect("timeout", this, "CheckClosedRoom");
	bool cor_col = get_node("Doors")->get_child(0)->call("_get_correct_colliding");
	Godot::print("correct colliding: " + String::num(cor_col));
	if (!cor_col) {
		this->queue_free();
	}
}

void godot::Room::IsCorrectPlaced()
{
	timer->disconnect("timeout", this, "IsCorrectPlaced");
	correct_placed = door_collisions.size() == 0;
	while (!correct_placed)
	{
		Respawn();
		return;
	}


	if (closed_room)
	{
		timer->connect("timeout", this, "CheckClosedRoom");
		timer->start(1);
	}

	SpawnNeighborRooms();

	//	if room spawned correct
	generation->AddSpawnedRoom(this);

	Godot::print("Count " + String::num(generation->doorsCount));
	if (!closed_room)
		generation->doorsCount -= 1;
}













void godot::RoomSpawner::SpawnRoom()
{
	timer->connect("timeout", this, "_spawn");
	timer->set_wait_time(.1f);
	add_child(timer, true);
	timer->start();
}

godot::PackedScene* godot::RoomSpawner::GetRandomRoomFromArray(Array& list)
{
	RandomNumberGenerator* randomizer = RandomNumberGenerator::_new();
	randomizer->randomize();

	int rand = randomizer->randi_range(0, list.size() - 1);
	randomizer = nullptr;
	return cast_to<PackedScene>(list[rand]);
}

void godot::RoomSpawner::_register_methods()
{
	register_method("_ready", &RoomSpawner::_ready);
	register_method("_spawn", &RoomSpawner::_spawn);
	register_method("_get_spawned", &RoomSpawner::_get_spawned);
	register_method("_get_spawn_direction", &RoomSpawner::_get_spawn_direction);
	register_method("_get_instance", &RoomSpawner::_get_instance);
	register_method("_on_Area2D_area_entered", &RoomSpawner::_on_Area2D_area_entered);

	register_property<RoomSpawner, String>("Direction", &RoomSpawner::spawn_direction, "");

}

void godot::RoomSpawner::_init()
{
}

void godot::RoomSpawner::_ready()
{
	generation_ref = get_node("/root/Node2D")->call("_get_instance");
	room_ref = get_parent()->get_parent()->call("_get_instance");
}

void godot::RoomSpawner::_on_Area2D_area_entered(Node* node)
{
	if (node->get_name().find("Checker") != -1 || node->get_name().find("Destroyer") != -1)
	{
		spawned = true;
		this->queue_free();
		return;
	}
	if (node->get_name().find("Spawner") != -1)
	{
		Godot::print("crossed closed room");
		if ((bool)node->call("_get_spawned") == false && spawned == false)
		{
			auto spawned_room = cast_to<Node2D>(generation_ref->closed_room->instance());
			spawned_room->set_global_position(this->get_global_position());
			spawned_room->call("_add_door_direction", spawn_direction, 1);
			spawned_room->call("_add_door_direction", node->call("_get_spawn_direction"), 1);
			Godot::print(node->call("_get_spawn_direction"));
			get_node("/root/Node2D/Rooms")->add_child(spawned_room, true);
			node->queue_free();
			this->queue_free();
		}
		spawned = true;
	}
}

void godot::RoomSpawner::_spawn()
{
	timer->disconnect("timeout", this, "_spawn");

    if (spawned == false)
    {
        if (generation_ref->doorsCount <= 0)
        {
            //  spawn closed room
            auto spawned_room = cast_to<Node2D>(generation_ref->GetClosedRoomByDirection(spawn_direction)->instance());

            spawned_room->set_global_position(this->get_global_position());
            get_node("/root/Node2D")->get_node("Rooms")->add_child(spawned_room, true);

            queue_free();
            spawned = true;
            return;
        }
        else
        {
            PackedScene *room_to_spawn = cast_to<PackedScene>(generation_ref->closed_room->instance());

            Array list = generation_ref->crossed_room->GetListByDirection(spawn_direction);

			if (room_ref->start_room) {

                room_to_spawn = GetRandomRoomFromArray(list);
			}

            if (!room_ref->start_room)
            {

                auto spawned_closed_room = cast_to<Node2D>(generation_ref->closed_room->instance());
                spawned_closed_room->set_global_position(this->get_global_position());
                spawned_closed_room->call("_add_door_direction", spawn_direction, 1);
				get_node("/root/Node2D")->get_node("Rooms")->add_child(spawned_closed_room, true);

            }
            else
            {

                auto r = cast_to<Node2D>(room_to_spawn->instance());
				r->set_global_position(this->get_global_position());
                get_node("/root/Node2D")->get_node("Rooms")->add_child(r, true);

            }

            spawned = true;
            queue_free();
            return;
        }
    }

}

bool godot::RoomSpawner::_get_spawned()
{
	return this->spawned;
}

godot::String godot::RoomSpawner::_get_spawn_direction()
{
	return this->spawn_direction;
}

godot::RoomSpawner* godot::RoomSpawner::_get_instance()
{
	return this;
}

godot::RoomSpawner::RoomSpawner()
{
	timer = Timer::_new();
}

godot::RoomSpawner::~RoomSpawner()
{
}
