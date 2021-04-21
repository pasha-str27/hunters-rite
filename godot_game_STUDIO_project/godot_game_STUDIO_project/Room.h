#pragma once

#include <Godot.hpp>
#include <Node2D.hpp>
#include <Array.hpp>
#include <RandomNumberGenerator.hpp>
#include "Generation.h"
#include "CustomExtensions.h"

namespace godot {
	class Room: public Node2D
	{
	private:
		GODOT_CLASS(Room, Node2D);
		Generation* generation = nullptr;
		void Respawn();
	public:
		Array doors = {};				//	strings 
		bool closed_room = false;		//	is room has 1 door
		bool start_room = false;
		Array possible_rooms = {};		//	array of possible rooms
		Array door_collisions = {};		//	array with collisions
		bool correct_placed = false;	//	is correct

		bool done = false;	//	room is completed

		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		Array _get_directions();
		void _add_door_collision(String dir);
		Room();
		~Room();
	};
}


