#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Room : public Node2D
	{
		GODOT_CLASS(Room, Node2D);
		std::map<Vector2, Node2D*> adjacent_rooms;
		int num_of_adjacent_rooms = 0;

		std::vector<std::vector<int>> room_map;

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
		void print();
	};
}