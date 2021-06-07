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

		int keys_frequency = 5;

		float step_x = 1024;
		float step_y = 720;

		std::vector<Vector2> positions;
		std::vector<Node2D*> rooms;

		int wall_top_count;
		int floor_count;
		int stone_count;
		int spike_count;
		int roof_count;

		//	for tests
		Ref<PackedScene> key_room_sprite = nullptr;
		Ref<PackedScene> item_room_sprite = nullptr;
		Ref<PackedScene> boss_room_sprite = nullptr;

		Ref<PackedScene> jertovnik = nullptr;
		Ref<PackedScene> key_room_pedestal = nullptr;

	public:
		LevelGenerator();
		~LevelGenerator();
		static void _register_methods();
		void _init();
		void _ready();
		void _connect_rooms(Node2D *prev, Node2D* next, Vector2 dir);
		void _generate();
		bool _has_room(std::vector<Vector2> positions, Vector2 pos);
		void _buid_room(Vector2 dir);
		void _buid_doors();
		void _buid_roofs();
		void _buid_floors();
		void _buid_top_wall();
		void _buid_stones_first_step(Node2D* room);
		void _buid_stones_second_step(Node2D* room);
		void _buid_spikes_first_step(Node2D* room);
		void _buid_spikes_second_step(Node2D* room);
		void _build_doors(int start_index, int end_index);
		Node2D* _get_next_room(Vector2 current_room_position);
		std::vector<Node2D*> _get_corner_rooms();
		std::vector<Node2D*> _create_keys_rooms(std::vector<Node2D*> &cornered_rooms);
		void _rebuild_doors(std::vector<Node2D*>);
		void _rebuild_doors(Node2D*);
		void _create_item_room(std::vector<Node2D*>& cornered_rooms);
		void _create_boss_room(std::vector<Node2D*>& cornered_rooms);
		Node2D* _generate_room_to(Node2D* room);
		void _generate_key(Vector2 pos);
	};
}