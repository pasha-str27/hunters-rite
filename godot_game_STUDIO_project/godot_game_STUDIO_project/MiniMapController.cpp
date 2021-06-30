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

	grid = nullptr;
}

void godot::MiniMapController::_register_methods()
{
	register_method("_init", &MiniMapController::_init);
	register_method("_ready", &MiniMapController::_ready);
	register_method("_set_positions", &MiniMapController::_set_positions);
	

	register_property<MiniMapController, Texture*>("current_room", &MiniMapController::curr_room, nullptr);
	register_property<MiniMapController, Sprite*>("discovered_room", &MiniMapController::disc_room, nullptr);
	register_property<MiniMapController, Sprite*>("undiscovered_room", &MiniMapController::undisc_room, nullptr);
	register_property<MiniMapController, float>("zoom", &MiniMapController::zoom, 1.5f);
}

void godot::MiniMapController::_init()
{
}

void godot::MiniMapController::_ready()
{
	grid = cast_to<TextureRect>(find_node("Grid"));

	if (grid != nullptr)
		Godot::print("now we have grid");

	//rooms_positions = get_node("/root/Node2D/Node/Generation")->call("_get_rooms_positions");

	int offset = 16;

	rooms_positions = { Vector2(0, 0), Vector2(1, 0), Vector2(0, -1) };

	for (auto pos : rooms_positions)
	{
		Godot::print(pos);
		auto sp = Sprite::_new();
		sp->set_texture(curr_room);
		grid->add_child(sp);

	}

}

void godot::MiniMapController::_process()
{
}

void godot::MiniMapController::_set_positions()
{
	Node* generation = get_node("/root/Node2D/Node/Generation");
	Array arr = CustomExtensions::GetRoomsByType(generation, "item_room");
	items_positions = arr[0];
	arr = CustomExtensions::GetRoomsByType(generation, "heal_room");
	heal_positions = arr[0];
	arr = CustomExtensions::GetRoomsByType(generation, "key_room");
	keys_positions = arr[0];
	arr = CustomExtensions::GetRoomsByType(generation, "boss_room");
	boss_positions = arr[0];
}
