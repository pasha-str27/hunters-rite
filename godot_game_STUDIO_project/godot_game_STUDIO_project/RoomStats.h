#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class RoomStats: public Node2D
	{
	private:
		GODOT_CLASS(RoomStats, Node2D);
		String type = "room";
		Array enemies = {};
		int enemies_count = 5;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		String _get_type();
		Array _get_enemies();
		int _get_enemies_count();
		RoomStats();
		~RoomStats();
	};
}


