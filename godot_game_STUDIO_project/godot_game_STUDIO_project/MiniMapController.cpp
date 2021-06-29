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

	register_property<MiniMapController, Ref<PackedScene>>("current_room", &MiniMapController::curr_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("discovered_room", &MiniMapController::disc_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("undiscovered_room", &MiniMapController::undisc_room, nullptr);
	register_property<MiniMapController, float>("zoom", &MiniMapController::zoom, 1.5f);
}

void godot::MiniMapController::_init()
{
}

void godot::MiniMapController::_ready()
{
	if (!_loadResources())
		Godot::print("Something went wrong! Can not to load resources");

	grid = cast_to<TextureRect>(find_node("Grid"));

	if (grid != nullptr)
	{
		Godot::print("Grid loaded");

		//rooms_positions = LevelGenerator::_get_rooms_positions();

		grid_rect_size = grid->get_rect().get_size();

		curr_room_pos = grid_rect_size / 2;
		grid_scale = grid_rect_size / (get_viewport_rect().size * zoom);

	}

	rooms_positions = { Vector2(step_x, step_y), Vector2(0, step_y), Vector2(0, 0) };

	Godot::print("Rooms pos setted");

	std::vector<Vector2> fixed_rooms_positions;

	for (auto room : rooms_positions)
	{
		auto room_pos = (room - curr_room_pos) * grid_scale + grid_rect_size / 2;
		fixed_rooms_positions.push_back(room_pos);
	}

	Godot::print("Rooms pos fixed");

	for (auto pos : fixed_rooms_positions)
	{
		Godot::print(pos);

		auto room = cast_to<Node2D>(undisc_room->instance());
		room->set_position(pos);

		grid->add_child(room);

		Godot::print("Added sprite as child to grid");
	}

	Godot::print("Added sprites");

}

void godot::MiniMapController::_process()
{
}

bool godot::MiniMapController::_loadResources()
{
	ResourceLoader* rld = ResourceLoader::get_singleton();

	if (curr_room == nullptr)
		curr_room = rld->load("res://Assets/Prefabs/MiniMapUi/curr_room.tscn");
	if (disc_room == nullptr)
		disc_room = rld->load("res://Assets/Prefabs/MiniMapUi/disc_room.tscn");
	if (undisc_room == nullptr)
		undisc_room = rld->load("res://Assets/Prefabs/MiniMapUi/undisc_room.tscn");

	rld = nullptr;

	return true;
}
