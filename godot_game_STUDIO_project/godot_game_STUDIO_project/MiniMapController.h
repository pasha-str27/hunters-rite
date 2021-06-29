#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class MiniMapController : public MarginContainer
	{
	private:
		GODOT_CLASS(MiniMapController, MarginContainer);

		Ref<PackedScene> curr_room = nullptr;
		Ref<PackedScene> undisc_room = nullptr;
		Ref<PackedScene> disc_room = nullptr;

		TextureRect* grid = nullptr;

		std::vector<Vector2> rooms_positions;
		std::vector<Vector2> disc_rooms_positions;
		Vector2 curr_room_position;

		float zoom = 1.5;
		float step_x = 1024;
		float step_y = 720;

		Vector2 grid_scale = Vector2::ZERO;
		Vector2 grid_rect_size = Vector2::ZERO;
		Vector2 players_pos = Vector2::ZERO;

		Array all_rooms = {};

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();

		bool _load_resources();
		void _update_minimap();
		Vector2 _get_players_pos();
		Vector2 _normalize_room_pos(Vector2 old_pos);
		void _clear_map();
		std::vector<Vector2> _normalize_all_rooms(std::vector<Vector2> rooms_pos_array);
		void _load_disc_rooms(std::vector<Vector2> disc_rooms_pos);
		void _load_curr_room(Vector2 curr_room_pos);
		void _load_undisc_rooms(std::vector<Vector2> undisc_rooms_pos);
		bool _is_on_grid(Vector2 pos);

		MiniMapController();
		~MiniMapController();
	};
}