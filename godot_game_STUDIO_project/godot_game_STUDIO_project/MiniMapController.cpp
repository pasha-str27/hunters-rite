#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::MiniMapController::MiniMapController()
{
}

godot::MiniMapController::~MiniMapController()
{
	curr_room = nullptr;
	undisc_room = nullptr;
	disc_room = nullptr;
}

void godot::MiniMapController::_register_methods()
{
	register_method("_init", &MiniMapController::_init);
	register_method("_ready", &MiniMapController::_ready);
	register_method("_status_checker", &MiniMapController::_status_checker);

	register_property<MiniMapController, Sprite*>("current_room", &MiniMapController::curr_room, nullptr);
	register_property<MiniMapController, Sprite*>("discovered_room", &MiniMapController::disc_room, nullptr);
	register_property<MiniMapController, Sprite*>("undiscovered_room", &MiniMapController::undisc_room, nullptr);
	register_property<MiniMapController, float>("zoom", &MiniMapController::zoom, 1.5f);
}

void godot::MiniMapController::_init()
{
}

void godot::MiniMapController::_ready()
{
	Godot::print("here");
	_status_checker();
	add_child(get_node("res://Assets/Sprites/GameIcon.png"));
}

void godot::MiniMapController::_process()
{
}

void godot::MiniMapController::_status_checker()
{
	Godot::print("show me something");
}
