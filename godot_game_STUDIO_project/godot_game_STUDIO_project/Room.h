#pragma once

#include <Godot.hpp>
#include <Node2D.hpp>
#include <Array.hpp>

namespace godot {
	class Room: public Node2D
	{
	private:
		GODOT_CLASS(Room, Node2D);
	public:
		Array doors = {};

		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		Array _get_directions();
	};
}


