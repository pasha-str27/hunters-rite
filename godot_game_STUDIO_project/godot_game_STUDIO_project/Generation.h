#pragma once
#include <Godot.hpp>
#include <PackedScene.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <Tree.hpp>
#include <Array.hpp>
#include <OS.hpp>

namespace godot
{
	class CrossedRoom: public Node2D {
	private:
		GODOT_CLASS(CrossedRoom, Node2D);
	public:
		static void _register_methods();
		void _init();

		Array left_rooms = {};
		Array right_rooms = {};
		Array top_rooms = {};
		Array bottom_rooms = {};

		CrossedRoom* _get_instance();

		CrossedRoom();
		~CrossedRoom();
	};

	class Generation: public Node2D
	{
	private:
		GODOT_CLASS(Generation, Node2D);
		void InstanceAllRooms();
	public:
		Array all_rooms = {};
		Array all_rooms_spawned = {};
		Ref<PackedScene> closed_room = nullptr;

		Array spawned_rooms = {};
		int doorsCount = 5;

		CrossedRoom* crossed_room = nullptr;

		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);
		void _input(Variant ev);
		Array GetListByDirections(Array l);
		Generation();
		~Generation();
	};
}
