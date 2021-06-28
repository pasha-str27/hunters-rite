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
	all_rooms.clear();
}

void godot::MiniMapController::_register_methods()
{
	register_method("_init", &MiniMapController::_init);
	register_method("_ready", &MiniMapController::_ready);
	register_method("_load_resources", &MiniMapController::_load_resources);
	register_method("_update_minimap", &MiniMapController::_update_minimap);
	register_method("_get_players_pos", &MiniMapController::_get_players_pos);
	register_method("_normalize_room_pos", &MiniMapController::_normalize_room_pos);
	register_method("_clear_map()", &MiniMapController::_clear_map);
	register_method("_normalize_all_rooms", &MiniMapController::_normalize_all_rooms);
	
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
	if (!_load_resources())
		Godot::print("Something went wrong! Can not to load resources");

	grid = cast_to<TextureRect>(find_node("Grid"));

	if (grid != nullptr)
	{
		Godot::print("Grid loaded");

		//rooms_positions = LevelGenerator::_get_rooms_positions();

		grid_rect_size = grid->get_rect().get_size();

		curr_room_marker_pos = grid_rect_size / 2;
		grid_scale = grid_rect_size / (get_viewport_rect().size * zoom);
	}
	else
	{
		Godot::print("Can not load grid");
		return;
	}

	rooms_positions =
	{
		Vector2(0, 0),
		Vector2(0, -step_y),
		Vector2(step_x, -step_y),
		Vector2(2 * step_x, -step_y),
		Vector2(-step_x, step_y),
		Vector2(0, step_y),
		Vector2(0, 2 * step_y),
		Vector2(step_x, 2 * step_y)
	};

	Godot::print("Rooms pos setted");

	players_pos = _get_players_pos();
	Godot::print(players_pos);
	Godot::print("Players pos setted");

	Godot::print("Rooms pos fixed: ");

	for (auto pos : _normalize_all_rooms())
	{
		Godot::print(pos);

		if (grid->get_rect().has_point(pos + grid->get_rect().position))
		{
			auto room = cast_to<Node2D>(undisc_room->instance());
			room->set_position(pos);
			room->set_scale(Vector2(4, 4));
			grid->add_child(room);
		}
		else
			Godot::print("Pos of room is out of range");
	}
	Godot::print("Added sprites");

	all_rooms = grid->get_children();

	_update_minimap();
}

void godot::MiniMapController::_process()
{
}

bool godot::MiniMapController::_load_resources()
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

void godot::MiniMapController::_update_minimap()
{
	Node2D* room = nullptr;

	for (int i = 0; i < all_rooms.size(); ++i)
	{
		room = cast_to<Node2D>(all_rooms[i]);

		if (rooms_positions[i] == players_pos)
		{
			room->queue_free();
			auto room = cast_to<Node2D>(curr_room->instance());
			room->set_position(_normalize_room_pos(players_pos));
			room->set_scale(Vector2(4, 4));
			grid->add_child(room);
		}
	}
}

Vector2 godot::MiniMapController::_get_players_pos()
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	int random_x = rng->randi_range(-2 * step_x, 2 * step_x);
	int random_y = rng->randi_range(-2 * step_y, 2 * step_y);

	Godot::print(Vector2(random_x, random_y));

	int fixed_random_x = (int)(random_x / step_x) * step_x;
	int fixed_random_y = (int)(random_y / step_y) * step_y;

	rng = nullptr;

	return Vector2(fixed_random_x, fixed_random_y);
}

Vector2 godot::MiniMapController::_normalize_room_pos(Vector2 old_pos)
{
	return (old_pos - players_pos) * grid_scale + grid_rect_size / 2;
}

void godot::MiniMapController::_clear_map()
{
	for (int i = 0; i < grid->get_child_count(); ++i)
		grid->get_child(i)->queue_free();
}

std::vector<Vector2> godot::MiniMapController::_normalize_all_rooms()
{
	std::vector<Vector2> fixed_rooms_positions;

	for (auto old_pos : rooms_positions)
	{
		auto room_pos = _normalize_room_pos(old_pos);
		fixed_rooms_positions.push_back(room_pos);
	}

	return fixed_rooms_positions;
}
