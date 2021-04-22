#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <Array.hpp>
#include <RandomNumberGenerator.hpp>
#include <Timer.hpp>
#include "Generation.h"
#include "CustomExtensions.h"

namespace godot {
	class RoomSpawner;

	class Room: public Node2D
	{
	private:
		GODOT_CLASS(Room, Node2D);
		Generation* generation = nullptr;
		Timer* timer = nullptr;

		void Respawn();
		Array SetUpPossibleRooms();
		void SpawnNeighborRooms();
		void CheckClosedRoom();
		
		bool need_to_spawn = false;
		RoomSpawner* current = nullptr;
	public:
		Array doors = {};				//	strings 
		bool closed_room = false;		//	is room has 1 door
		bool start_room = false;		//	is it start room
		Array possible_rooms = {};		//	array of possible rooms
		Array door_collisions = {};		//	array with collisions
		bool correct_placed = false;	//	is correct
		bool done = false;				//	room is completed

		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		Room* _get_instance();
		Array _get_directions();
		void _add_door_collision(String dir);
		void _set_possible_rooms(Array a);
		void _wait_to_spawn();
		Room();
		~Room();
	};

	class RoomSpawner : public Node2D
	{
	private:
		GODOT_CLASS(RoomSpawner, Node2D);
		Room* room_ref = nullptr;
		bool spawned = false;
		Generation* generation_ref = nullptr;
		PackedScene* GetRandomRoomFromArray(Array& list);
		Timer* timer = nullptr;
	public:
		String spawn_direction;
		static void _register_methods();
		void _init();
		void _ready();
		void _on_Area2D_area_entered(Node* node);
		void _spawn();
		bool _get_spawned();
		void SpawnRoom();
		RoomSpawner* _get_instance();
		RoomSpawner();
		~RoomSpawner();
	};
}
