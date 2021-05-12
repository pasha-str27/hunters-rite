#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::RoomStats::_register_methods()
{
	register_method("_get_type", &RoomStats::_get_type);
	register_method("_get_enemies", &RoomStats::_get_enemies);
	register_method("_get_enemies_count", &RoomStats::_get_enemies_count);

	register_property<RoomStats, String>("Type", &RoomStats::type, "room");
	register_property<RoomStats, Array>("Enemies", &RoomStats::enemies, {});
	register_property<RoomStats, int>("Enemies count", &RoomStats::enemies_count, 5);
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

int godot::RoomStats::_get_enemies_count()
{
	return this->enemies_count;
}

godot::RoomStats::RoomStats()
{
}

godot::RoomStats::~RoomStats()
{
	type = "";
	enemies.clear();
}
