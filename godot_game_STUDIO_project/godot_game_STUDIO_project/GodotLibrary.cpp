#include "texture.h"
#include "Generation.h"
#include "PlayerController.h"
#include "SpawnPointChecker.h"
#include "Room.h"
#include "Destroyer.h"
#include "ClosedRoom.h"
#include "Door.h"
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif


using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o)
{
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o)
{
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle)
{
	Godot::nativescript_init(handle);

	register_class<Generation>();
	register_class<CrossedRoom>();
	register_class<ClosedRoom>();
	register_class<Room>();
	register_class<Destroyer>();
	register_class<SpawnPointChecker>();
	register_class<Door>();
	register_class<RoomSpawner>();

	register_class<PlayerController>();
	register_class<Bullet>();
	register_class<Enemy>();
	register_class<Sword>();
	register_class<CameraController>();
	register_class<Spike>();

}