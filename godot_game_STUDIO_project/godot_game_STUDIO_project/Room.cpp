#include "Room.h"

void godot::Room::Respawn()
{
	if (possible_rooms.size() == 0)
		//CustomExtensions::AddRange(possible_rooms, SetUpPossibleRooms());

	if (possible_rooms.size() == 0)
	{
		//Instantiate(possible_rooms.closedRoom, transform.position, generation.closedRoom.transform.rotation);
		queue_free();
		return;
	}

	//  respawn to random room
	RandomNumberGenerator *randomizer = RandomNumberGenerator::_new();
	int rand = randomizer->randi_range(0, possible_rooms.size());

	//AddRoom newRoom = Instantiate(possibleRooms[rand], transform.position, possibleRooms[rand].transform.rotation).GetComponent<AddRoom>();
	//  delete from list spawned
	possible_rooms.remove(rand);
	//newRoom.possibleRooms = possibleRooms;
	//  delete this room
	//gameObject.SetActive(false);
	queue_free();
}

void godot::Room::_register_methods()
{
	register_method("_ready", &Room::_ready);
	register_method("_process", &Room::_process);
	register_method("_add_door_collision", &Room::_add_door_collision);
	register_method("_get_directions", &Room::_get_directions);
	register_property<Room, Array>("doors", &Room::doors, {});
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
}

void godot::Room::_process()
{
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

godot::Room::Room()
{
}

godot::Room::~Room()
{
	generation = nullptr;
	doors.clear();
}


