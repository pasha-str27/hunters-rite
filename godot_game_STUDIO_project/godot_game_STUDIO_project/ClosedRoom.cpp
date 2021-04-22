#include "ClosedRoom.h"
#include "Generation.h"
#include "CustomExtensions.h"

void godot::ClosedRoom::SpawnPossibleRoom()
{
    timer->disconnect("timeout", this, "SpawnPossibleRoom");
    //timer->queue_free();
    Godot::print("Closed Room spawning");
    //  get correct list
    Generation *templates = get_node("/root/Node2D")->call("_get_instance");
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
    auto new_room = cast_to<PackedScene>(possible_rooms[rand])->instance();
    //  delete spawned room from possible list
    possible_rooms.remove(rand);
    //  set possible list
    new_room->call("_set_possible_rooms", possible_rooms, 1);
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
    timer->set_wait_time(0.1f);
    add_child(timer);
    Godot::print("Timer started");
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
