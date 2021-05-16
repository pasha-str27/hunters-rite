#pragma once
#include <Godot.hpp>
#include <Node2D.hpp>
#include <Timer.hpp>

namespace godot {
	class ClosedRoom: public Node2D
	{
	private:
		GODOT_CLASS(ClosedRoom, Node2D);
		void SpawnPossibleRoom();
		Timer* timer = nullptr;
	public:

		Array door_directions;

		static void _register_methods();
		void _init();
		void _ready();
		void _add_door_direction(String dir);
		ClosedRoom();
		~ClosedRoom();
	};
}


