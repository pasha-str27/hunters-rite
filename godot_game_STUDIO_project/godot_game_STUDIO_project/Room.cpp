#include "Room.h"

void godot::Room::_register_methods()
{
	register_method("_ready", &Room::_ready);
	register_method("_get_directions", &Room::_get_directions);
	register_property<Room, Array>("doors", &Room::doors, {});	
}

void godot::Room::_init()
{

}

void godot::Room::_ready()
{
}

void godot::Room::_process()
{
}

godot::Array godot::Room::_get_directions()
{
	return this->doors;
}


