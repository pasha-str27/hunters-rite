#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::RoomStats::_register_methods()
{
	register_method("_get_type", &RoomStats::_get_type);
	register_method("_get_enemies", &RoomStats::_get_enemies);

	register_property<RoomStats, String>("Type", &RoomStats::type, "room");
	register_property<RoomStats, Array>("Enemies", &RoomStats::enemies, {});
}

void godot::RoomStats::_init()
{
}

void godot::RoomStats::_ready()
{
}

String godot::RoomStats::_get_type()
{
	return this->type;
}

Array godot::RoomStats::_get_enemies()
{
	return this->enemies;
}

godot::RoomStats::RoomStats()
{
}

godot::RoomStats::~RoomStats()
{
	type = "";
	enemies.clear();
}
