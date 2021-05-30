#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class LevelGenerator :	public Node
	{
		GODOT_CLASS(LevelGenerator, Node);
		int map_size = 10;
		int size = 0;
		Ref<PackedScene> room = nullptr;
		Ref<PackedScene> up_door = nullptr;
		Ref<PackedScene> right_door = nullptr;
		Ref<PackedScene> down_door = nullptr;
		Ref<PackedScene> left_door = nullptr;

		float step_x = 1024;
		float step_y = 720;

		std::vector<Vector2> positions;
		std::vector<Node2D*> rooms;

	public:
		LevelGenerator();
		static void _register_methods();
		void _init();
		void _ready();
		void _connect_rooms(Node2D *prev, Node2D* next, Vector2 dir);
		void _generate();
		bool _has_room(std::vector<Vector2> positions, Vector2 pos);
		void _buid_room(Vector2 dir);
		void _buid_doors();
		Node2D* _get_next_room(Vector2 current_room_position);
	};
}