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

		Ref<PackedScene> up_door_fill = nullptr;
		Ref<PackedScene> right_door_fill = nullptr;
		Ref<PackedScene> down_door_fill = nullptr;
		Ref<PackedScene> left_door_fill = nullptr;

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

		Ref<PackedScene> jertovnik = nullptr;
		Ref<PackedScene> key_room_pedestal = nullptr;

		Array keys_prefabs = {};
		Array keys_prefabs_local = {};
		Array generated_keys = {};
		std::vector<Color> generated_colors_keys;

		Ref<PackedScene> big_stone = nullptr;
		Ref<PackedScene> lock_sprite = nullptr;

	public:
		LevelGenerator();
		~LevelGenerator();
		static void _register_methods();
		void _init();
		void _ready();
		void _connect_rooms(Node2D *prev, Node2D* next, Vector2 dir);
		void _generate();
		bool _has_room(std::vector<Vector2> positions, Vector2 pos);
		Node2D* _buid_room(Vector2 dir);
		void _buid_doors();
		void _buid_roofs();
		void _buid_floors();
		void _buid_top_wall();
		void _buid_stones(Node2D* room);
		void _buid_spikes(Node2D* room);
		void _build_doors(int start_index, int end_index);
		Node2D* _get_next_room(Vector2 current_room_position);
		std::vector<Node2D*> _get_corner_rooms();
		std::vector<Node2D*> _create_keys_rooms(std::vector<Node2D*> &cornered_rooms);
		void _rebuild_doors(std::vector<Node2D*>);
		void _rebuild_doors(Node2D*);
		void _create_item_room(std::vector<Node2D*>& cornered_rooms);
		Node2D* _create_boss_room(std::vector<Node2D*>& cornered_rooms);
		Node2D* _generate_room_to(Node2D* room);
		void _generate_key(Node2D* room);
		void _set_keys(Node2D* room, Array keys);
		void _spawn_big_stone();
		int _get_keys_count();
		void _clear();
		Array _get_rooms();
		Array _get_rooms_positions();
		void _build_locks();
		void _build_locks_in_room(Node2D* room, Vector2 door_dir, String door_name, int step);
		void _build_fill_doors();
	};
}