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
		Timer* timer = nullptr;

		bool need_to_spawn = false;
		RoomSpawner* current = nullptr;

		Array _respawn_dirs = {};
		
		void Respawn();
		Array SetUpPossibleRooms();
		void SpawnNeighborRooms();
		void CheckClosedRoom();
		void IsCorrectPlaced();
		void  _respawn();

	public:
		Generation* generation = nullptr;
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
		void PrepareToRespawn(String dir);
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
		Timer* timer = nullptr;
		PackedScene* GetRandomRoomFromArray(Array& list);
	public:
		String spawn_direction;
		static void _register_methods();
		void _init();
		void _ready();
		void _on_Area2D_area_entered(Node* node);
		void _spawn();
		bool _get_spawned();
		String _get_spawn_direction();
		void SpawnRoom();
		RoomSpawner* _get_instance();
		RoomSpawner();
		~RoomSpawner();
	};
}
