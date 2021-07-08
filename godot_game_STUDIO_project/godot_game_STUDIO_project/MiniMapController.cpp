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
	key_room = nullptr;
	heal_room = nullptr;
	item_room = nullptr; 
	boss_room = nullptr;

	grid = nullptr;
	timer = nullptr;

	disc_rooms_positions.clear();
	undisc_rooms_positions.clear();
	keys_positions.clear();
	items_positions.clear();
	heal_positions.clear();
	boss_positions.clear();
}

void godot::MiniMapController::_register_methods()
{
	register_method("_init", &MiniMapController::_init);
	register_method("_ready", &MiniMapController::_ready);

	register_method("_set_positions", &MiniMapController::_set_positions);
	register_method("_load_resources", &MiniMapController::_load_resources);
	register_method("_update_minimap", &MiniMapController::_update_minimap);
	register_method("_get_players_pos", &MiniMapController::_get_players_pos);
	register_method("_normalize_room_pos", &MiniMapController::_normalize_room_pos);
	register_method("_clear_map", &MiniMapController::_clear_map);
	register_method("_normalize_all_rooms", &MiniMapController::_normalize_all_rooms);
	register_method("_load_curr_room", &MiniMapController::_load_curr_room);
	register_method("_load_undisc_rooms", &MiniMapController::_load_undisc_rooms);
	register_method("_is_on_grid", &MiniMapController::_is_on_grid);
	register_method("_load_special_rooms", &MiniMapController::_load_special_rooms);
	register_method(" _special_rooms_loader", &MiniMapController::_special_rooms_loader);
	register_method("_update_special_rooms", &MiniMapController::_update_special_rooms);
	register_method("_start_treking", &MiniMapController::_start_treking);

	register_method("_start_timer", &MiniMapController::_start_timer);
	register_method("_on_timeout", &MiniMapController::_on_timeout);
	
	register_property<MiniMapController, Ref<PackedScene>>("current_room", &MiniMapController::curr_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("discovered_room", &MiniMapController::disc_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("undiscovered_room", &MiniMapController::undisc_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("key_room", &MiniMapController::key_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("item_room", &MiniMapController::item_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("heal_room", &MiniMapController::heal_room, nullptr);
	register_property<MiniMapController, Ref<PackedScene>>("boss_room", &MiniMapController::boss_room, nullptr);
	register_property<MiniMapController, float>("zoom", &MiniMapController::zoom, 1.5f);
}

void godot::MiniMapController::_init()
{
}

void godot::MiniMapController::_ready()
{
	//if(CameraController::current_level>=2)
	//	_clear_map();
	disc_rooms_positions.clear();
	undisc_rooms_positions.clear();
	key_rooms_positions.clear();
	item_rooms_positions.clear();
	boss_rooms_positions.clear();
	heal_rooms_positions.clear();
	keys_positions.clear();
	items_positions.clear();
	heal_positions.clear();
	boss_positions.clear();
	//_start_treking();
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
	if (key_room == nullptr)
		undisc_room = rld->load("res://Assets/Prefabs/MiniMapUi/key_room.tscn");
	if (item_room == nullptr)
		undisc_room = rld->load("res://Assets/Prefabs/MiniMapUi/item_room.tscn");
	if (heal_room == nullptr)
		undisc_room = rld->load("res://Assets/Prefabs/MiniMapUi/heal_room.tscn");
	if (boss_room == nullptr)
		undisc_room = rld->load("res://Assets/Prefabs/MiniMapUi/boss_room.tscn");


	grid = cast_to<TextureRect>(find_node("Grid"));

	if (grid != nullptr)
	{
		Godot::print("now we have grid");

		grid_rect_size = grid->get_rect().get_size();

		_set_positions();

		Godot::print(undisc_rooms_positions.size());

		curr_room_position = grid_rect_size / 2;
		grid_scale = grid_rect_size / (get_viewport_rect().size * zoom);
	}
	else
	{
		Godot::print("Grid wasn't loaded");
		return false;
	}

	rld = nullptr;

	return true;
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
	undisc_rooms_positions = get_node("/root/Node2D/Node/Generation")->call("_get_rooms_positions");
	undisc_rooms_positions = undisc_rooms_positions[0];
}

void godot::MiniMapController::_update_minimap()
{
	Node2D* room = nullptr;

	Godot::print("Getting players pos");
	players_pos = _get_players_pos();

	if (undisc_rooms_positions.size() > 0
		|| disc_rooms_positions.size() > 0
		|| key_rooms_positions.size() > 0
		|| item_rooms_positions.size() > 0
		|| heal_rooms_positions.size() > 0
		|| boss_rooms_positions.size() > 0)
	{
		if (undisc_rooms_positions.find(players_pos) != -1)
		{
			_clear_map();
			_load_curr_room(players_pos);
			_special_rooms_loader(disc_rooms_positions,
				key_rooms_positions,
				item_rooms_positions,
				heal_rooms_positions,
				boss_rooms_positions);

			if (keys_positions.find(players_pos) != -1)
				key_rooms_positions.push_back(players_pos);
			else if (items_positions.find(players_pos) != -1)
				item_rooms_positions.push_back(players_pos);
			else if (heal_positions.find(players_pos) != -1)
				heal_rooms_positions.push_back(players_pos);
			else if (boss_positions.find(players_pos) != -1)
				boss_rooms_positions.push_back(players_pos);
			else
				disc_rooms_positions.push_back(players_pos);

			undisc_rooms_positions.remove(undisc_rooms_positions.find(players_pos));

			_load_undisc_rooms(undisc_rooms_positions);

			return;
		}
		else
			_update_special_rooms();
		Godot::print("Players pos is out of range");
	}
	else
		Godot::print("There are no rooms");
}

Vector2 godot::MiniMapController::_get_players_pos()
{
	auto player = CameraController::current_room->get_global_position();

	int fixed_x = (int)(player.x / step_x) * step_x;
	int fixed_y = (int)(player.y / step_y) * step_y;

	Godot::print(Vector2(fixed_x, fixed_y));

	return Vector2(fixed_x, fixed_y);
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

Array godot::MiniMapController::_normalize_all_rooms(Array rooms_pos_array)
{
	Array fixed_rooms_positions;

	for (int i = 0; i < rooms_pos_array.size(); ++i)
	{
		Vector2 room_pos = _normalize_room_pos(rooms_pos_array[i]);
		fixed_rooms_positions.push_back(room_pos);
	}

	return fixed_rooms_positions;
}

void godot::MiniMapController::_load_curr_room(Vector2 curr_room_pos)
{
	auto room = cast_to<Node2D>(curr_room->instance());
	room->set_position(_normalize_room_pos(curr_room_pos));
	room->set_scale(room_icon_scale);
	grid->add_child(room);
}

void godot::MiniMapController::_load_undisc_rooms(Array undisc_rooms_pos)
{
	for (int i = 0; i < undisc_rooms_pos.size(); ++i)
	{
		Vector2 pos = _normalize_all_rooms(undisc_rooms_pos)[i];
		if (_is_on_grid(pos))
		{
			auto room = cast_to<Node2D>(undisc_room->instance());
			room->set_position(pos);
			room->set_scale(room_icon_scale);
			grid->add_child(room);
		}
	}
}

void godot::MiniMapController::_load_special_rooms(Array rooms_pos, String type)
{
	for (int i = 0; i < rooms_pos.size(); ++i)
	{
		Vector2 pos = _normalize_all_rooms(rooms_pos)[i];
		if (_is_on_grid(pos))
		{
			Node2D* room = nullptr;

			if (type == "boss")
				room = cast_to<Node2D>(boss_room->instance());
			else if (type == "key")
				room = cast_to<Node2D>(key_room->instance());
			else if (type == "item")
				room = cast_to<Node2D>(item_room->instance());
			else if (type == "heal")
				room = cast_to<Node2D>(heal_room->instance());
			else
				room = cast_to<Node2D>(disc_room->instance());
		
			room->set_position(pos);
			room->set_scale(room_icon_scale);
			grid->add_child(room);
		}
	}
}

void godot::MiniMapController::_special_rooms_loader(Array dr, Array kr, Array ir, Array hr, Array br)
{
	_load_special_rooms(dr, "disc");
	_load_special_rooms(kr, "key");
	_load_special_rooms(ir, "item");
	_load_special_rooms(hr, "heal");
	_load_special_rooms(br, "boss");

}

void godot::MiniMapController::_update_special_rooms()
{
	_clear_map();
	_load_curr_room(players_pos);

	if (disc_rooms_positions.find(players_pos) != -1)
	{
		disc_rooms_positions.remove(disc_rooms_positions.find(players_pos));
		_special_rooms_loader(disc_rooms_positions, key_rooms_positions, item_rooms_positions, heal_rooms_positions, boss_rooms_positions);
		disc_rooms_positions.push_back(players_pos);
	}
	else if (key_rooms_positions.find(players_pos) != -1)
	{
		key_rooms_positions.remove(key_rooms_positions.find(players_pos));
		_special_rooms_loader(disc_rooms_positions, key_rooms_positions, item_rooms_positions, heal_rooms_positions, boss_rooms_positions);
		key_rooms_positions.push_back(players_pos);
	}
	else if (item_rooms_positions.find(players_pos) != -1)
	{
		item_rooms_positions.remove(item_rooms_positions.find(players_pos));
		_special_rooms_loader(disc_rooms_positions, key_rooms_positions, item_rooms_positions, heal_rooms_positions, boss_rooms_positions);
		item_rooms_positions.push_back(players_pos);
	}
	else if (heal_rooms_positions.find(players_pos) != -1)
	{
		heal_rooms_positions.remove(heal_rooms_positions.find(players_pos));
		_special_rooms_loader(disc_rooms_positions, key_rooms_positions, item_rooms_positions, heal_rooms_positions, boss_rooms_positions);
		heal_rooms_positions.push_back(players_pos);
	}
	else if (boss_rooms_positions.find(players_pos) != -1)
	{
		boss_rooms_positions.remove(boss_rooms_positions.find(players_pos));
		_special_rooms_loader(disc_rooms_positions, key_rooms_positions, item_rooms_positions, heal_rooms_positions, boss_rooms_positions);
		boss_rooms_positions.push_back(players_pos);
	}

	_load_undisc_rooms(undisc_rooms_positions);

	return;
}

bool godot::MiniMapController::_is_on_grid(Vector2 pos)
{
	return grid->get_rect().has_point(pos + grid->get_rect().position);
}

void godot::MiniMapController::_start_treking()
{
	if (CameraController::current_level >= 2)
		//	_clear_map();
	{
		disc_rooms_positions.clear();
		undisc_rooms_positions.clear();
		key_rooms_positions.clear();
		item_rooms_positions.clear();
		boss_rooms_positions.clear();
		heal_rooms_positions.clear();
		keys_positions.clear();
		items_positions.clear();
		heal_positions.clear();
		boss_positions.clear();
	}

	if (!_load_resources())
		Godot::print("Something went wrong! Resources weren't loaded");

	players_pos = _get_players_pos();
	Godot::print(players_pos);
	_load_undisc_rooms(undisc_rooms_positions);
	_update_minimap();
}

void godot::MiniMapController::_start_timer()
{
	if (!timer->is_connected("timeout", this, "_on_timeout"))
	{
		timer->connect("timeout", this, "_on_timeout");

		if (!has_node(NodePath(timer->get_name())))
			add_child(timer);

		timer->set_wait_time(2);
		timer->start();
	}
}

void godot::MiniMapController::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	_start_treking();
}
