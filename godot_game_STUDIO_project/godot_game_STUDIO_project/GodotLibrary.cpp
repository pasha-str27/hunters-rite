#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

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

	register_class<SpawnEnemyController>();
	register_class<PlayerController>();
	register_class<Bullet>();
	register_class<Enemy>();
	register_class<Sword>();
	register_class<CameraController>();
	register_class<Spike>();
	register_class<Item>();
	register_class<ReviveZone>();
	register_class<ItemsContainer>();
	register_class<ItemGenerator>();
	register_class<FadeAnimation>();
	register_class<RoomStats>();
	register_class<MenuButtons>();
	register_class<AudioEffect>();
	register_class<ParticlesDestroyer>();
	register_class<ExitHandler>();
	register_class<Preloader>();
	register_class<MagnitZone>();
	register_class<Room>();
	register_class<LevelGenerator>();
	register_class<BigStone>();
	register_class<Key>();
	register_class<EnemyPrice>();
	register_class<MiniMapController>();
	register_class<Ball>();
}