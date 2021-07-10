#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	struct data_to_spawn_enemy
	{
		Node2D* enemy;
		Vector2 new_pos;
		Timer* timer;
	};

	class Room : public Node2D
	{
		GODOT_CLASS(Room, Node2D);
		std::map<Vector2, Node2D*> adjacent_rooms;
		int num_of_adjacent_rooms = 0;
		std::vector<std::vector<int>> room_map;
		std::vector<Vector2> empty_pos_world_coordinates;
		std::vector<data_to_spawn_enemy> enemies_to_spawn;
		Array list_of_keys;
		float room_difficulty = 100;
		String room_type = "";
		bool were_here = false;

		bool is_special = false;
		Color last_key_color = Color(1, 1, 1, 1);

	public:
		Room();
		~Room();
		static void _register_methods();
		void _init();
		void _ready();
		bool _adjacent_room_is_null(Vector2 pos);
		void _set_adjacent_room(Vector2 pos, Node2D* value);
		int _get_num_of_adjacent_rooms();
		void _set_num_of_adjacent_rooms(int value);
		bool _is_empty_pos(int i, int j);
		int _get_cell_value(int i, int j);
		void _set_cell_value(int i, int j, int value);
		void _fill_empty_positions(Node2D* room);
		void print();
		void _add_list(Array);
		Array _get_list_of_keys();
		int _get_key_count();
		String _get_room_type();
		void _set_room_type(String type);
		bool _get_were_here();
		void _set_were_here(bool value);
		void _set_is_special(bool value);
		bool _get_is_special();
		Array _get_enemy_spawn_positions();
		void _add_new_enemy(Node2D* room, Vector2 position);
		void _spawn_enemy(int number);
		void _clear_enemy_to_spawn();
		Color _get_last_key_color();
		void _set_last_key_color(Color color);
	};
}