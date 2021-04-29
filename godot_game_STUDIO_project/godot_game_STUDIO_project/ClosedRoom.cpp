#include "ClosedRoom.h"
#include "Generation.h"
#include "CustomExtensions.h"

void godot::ClosedRoom::SpawnPossibleRoom()
{
    timer->disconnect("timeout", this, "SpawnPossibleRoom");
    //  get correct list
    Generation *templates = get_node("/root/Node2D")->call("_get_instance");
    Godot::print("door directions in closed room spawn: " + String::num(door_directions.size()));
    Array possible_rooms = templates->GetListByDirections(door_directions);


    if (possible_rooms.size() == 0)
    {
        possible_rooms = templates->all_rooms;
        Godot::print("Zero in closed room spawn func");
        return;
    }

    //  get random room to spawn
    RandomNumberGenerator* randomizer = RandomNumberGenerator::_new();
    int rand = randomizer->randi_range(0, possible_rooms.size() - 1);
    randomizer = nullptr;

    //  spawn new room
    auto new_room = cast_to<Node2D>(cast_to<PackedScene>(possible_rooms[rand])->instance());
    Godot::print("33");
    new_room->set_global_position(this->get_global_position());
    //  delete spawned room from possible list
    possible_rooms.remove(rand);
    //  set possible list
    new_room->call("_set_possible_rooms", possible_rooms, 1);
    get_node("/root/Node2D")->get_node("Rooms")->add_child(new_room, true);
    //  destroy closed room
    this->queue_free();
}

void godot::ClosedRoom::_register_methods()
{
    register_method("_ready", &ClosedRoom::_ready);
    register_method("_add_door_direction", &ClosedRoom::_add_door_direction);
    register_method("SpawnPossibleRoom", &ClosedRoom::SpawnPossibleRoom);
}

void godot::ClosedRoom::_init()
{
}

void godot::ClosedRoom::_ready()
{
    timer->connect("timeout", this, "SpawnPossibleRoom");
    timer->set_wait_time(0.3f);
    add_child(timer);
    timer->start();
}

void godot::ClosedRoom::_add_door_direction(String dir)
{
	door_directions.push_back(dir);
}

godot::ClosedRoom::ClosedRoom()
{
    timer = Timer::_new();
}

godot::ClosedRoom::~ClosedRoom()
{
    timer = nullptr;
}
