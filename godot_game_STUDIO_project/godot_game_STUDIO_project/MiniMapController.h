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

		Array undisc_rooms_positions = {};
		Array disc_rooms_positions = {};
		Vector2 curr_room_position;

		Array keys_positions = {};
		Array items_positions = {};
		Array heal_positions = {};
		Array boss_positions = {};

		float zoom = 1.5;
		float step_x = 1024;
		float step_y = 720;

		Vector2 grid_scale = Vector2::ZERO;
		Vector2 grid_rect_size = Vector2::ZERO;
	    Vector2 players_pos = Vector2::ZERO;

		Vector2 room_icon_scale = Vector2(4, 4);

		Timer* timer = Timer::_new();

	public:
		static void _register_methods();
		void _init();
		void _ready();

		void _set_positions();
		bool _load_resources();
		void _update_minimap();
		Vector2 _get_players_pos();
		Vector2 _normalize_room_pos(Vector2 old_pos);
		void _clear_map();
		Array _normalize_all_rooms(Array rooms_pos_array);
		void _load_disc_rooms(Array  disc_rooms_pos);
		void _load_curr_room(Vector2 curr_room_pos);
		void _load_undisc_rooms(Array  undisc_rooms_pos);
		bool _is_on_grid(Vector2 pos);
		void _start_treking();

		void _start_timer();
		void _on_timeout();

		MiniMapController();
		~MiniMapController();
	};
}