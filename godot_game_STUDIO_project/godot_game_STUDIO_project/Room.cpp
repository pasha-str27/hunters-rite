#include "Room.h"
#include <Node.hpp>

void godot::Room::Respawn()
{
	if (possible_rooms.size() == 0) {
		Array new_possible_rooms = SetUpPossibleRooms();
		CustomExtensions::AddRange(possible_rooms, new_possible_rooms);
	}

	if (possible_rooms.size() == 0)
	{
		auto spawned_c_r = cast_to<Node2D>(generation->closed_room->instance());
		spawned_c_r->set_position(this->get_position());
		generation->add_child(spawned_c_r);
		this->queue_free();
		return;
	}

	//  respawn to random room
	RandomNumberGenerator* randomizer = RandomNumberGenerator::_new();
	int rand = randomizer->randi_range(0, possible_rooms.size() - 1);
	randomizer = nullptr;

	auto new_room = cast_to<PackedScene>(possible_rooms[rand])->instance();
	//  delete from list spawned
	possible_rooms.remove(rand);
	new_room->call("_set_possible_rooms", possible_rooms, 1);
	//  delete this room
	this->queue_free();
}

void godot::Room::_wait_to_spawn() {
	timer->disconnect("timeout", this, "_wait_to_spawn");
	Godot::print("_wait_to_spawn ended");
	need_to_spawn = true;
}

void godot::Room::_register_methods()
{
	register_method("_ready", &Room::_ready);
	register_method("_process", &Room::_process);
	register_method("_add_door_collision", &Room::_add_door_collision);
	register_method("_get_directions", &Room::_get_directions);
	register_method("_get_instance", &Room::_get_instance);	
	register_method("_set_possible_rooms", &Room::_set_possible_rooms);
	register_method("_wait_to_spawn", &Room::_wait_to_spawn);
	
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

	//	if room spawned correct
	generation->AddSpawnedRoom(this);
	generation->doorsCount -= 1;

	SpawnNeighborRooms();
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
	possible_rooms = CustomExtensions::FindAll(possible_rooms, [dir](Node* node) {
		Array arr = node->call("_get_directions");
		return !arr.has(dir);
	});
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
	return CustomExtensions::FindAll(generation->GetListByDirections(doors), [this](Node* x) {
		Array dirs = x->call("_get_directions");
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
		timer->connect("timeout", this, "_wait_to_spawn", arr[i]);
		add_child(timer);
		Godot::print("_wait_to_spawn started");
		timer->start(0.5f);
		if(arr[i] != nullptr)
			current = arr[i];

		Godot::print("something else");
		
	}
	//Array children = transform.GetComponentsInChildren<RoomSpawner>();
	//for(var item in children)
	//{
	   // if (item == null)
	   //	 continue;
	   // yield return new WaitForSeconds(0.03f);
	   // item.SpawnRoom();
	//}
}



void godot::Room::CheckClosedRoom()
{
	//if (!transform.GetComponentInChildren<Door>().GetCorrectColliding())
	//{
	   // this->queue_free();
	//}
}

//void godot::Room::SpawnRoom(RoomSpawner* spawner)
//{
//
//}


void godot::RoomSpawner::SpawnRoom()
{
	timer->connect("timeout", this, "_spawn");
	timer->set_wait_time(.1f);
	add_child(timer);
	timer->start();
}

godot::PackedScene* godot::RoomSpawner::GetRandomRoomFromArray(Array& list)
{
	RandomNumberGenerator* randomizer = RandomNumberGenerator::_new();
	int rand = randomizer->randi_range(0, list.size() - 1);
	randomizer = nullptr;
	return cast_to<PackedScene>(list[rand]);
}

void godot::RoomSpawner::_register_methods()
{
	register_method("_ready", &RoomSpawner::_ready);
	register_method("_spawn", &RoomSpawner::_spawn);
	register_method("_get_spawned", &RoomSpawner::_get_spawned);
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
}

void godot::RoomSpawner::_spawn()
{
	//timer->disconnect("timeout", this, "_spawn");
	Godot::print("101");

    if (spawned == false)
    {
        if (generation_ref->doorsCount <= 0)
        {
            //  spawn closed room
            auto spawned_room = cast_to<Node2D>(CustomExtensions::Find(generation_ref->closed_rooms, [this](Node* node) {
                Array arr = node->call("_get_directions");
                for (int i = 0; i < arr.size(); i++) {
                    if (arr[i] == spawn_direction)
                        return true;
                }
                return false;
                
            })->instance());
            spawned_room->set_position(this->get_position());
            get_node("/root/Node2D")->get_node("Rooms")->add_child(spawned_room);

            queue_free();
            spawned = true;
            return;
        }
        else
        {
            PackedScene *room_to_spawn = cast_to<PackedScene>(generation_ref->closed_room->instance());

            Array list = generation_ref->crossed_room->GetListByDirection(spawn_direction);
			Godot::print(String::num(generation_ref->closed_room == nullptr));

			if (room_ref->start_room) {
				Godot::print("5511");

                room_to_spawn = GetRandomRoomFromArray(list);
			}
			Godot::print("113");

            if (!room_ref->start_room)
            {
				Godot::print("114");
				Godot::print(String::num(room_to_spawn == nullptr));

                auto spawned_closed_room = cast_to<Node2D>(generation_ref->closed_room->instance(1));
				Godot::print(String::num(spawned_closed_room == nullptr));
                spawned_closed_room->set_global_position(this->get_global_position());
                spawned_closed_room->call("_add_door_direction", spawn_direction);
            }
            else
            {
				Godot::print("116");

                auto r = cast_to<Node2D>(room_to_spawn->instance());
                get_node("/root/Node2D")->get_node("Rooms")->add_child(r);
				r->set_global_position(this->get_global_position());

            }
			Godot::print("171");

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
