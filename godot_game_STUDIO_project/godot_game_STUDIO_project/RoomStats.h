#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class RoomStats: public Node2D
	{
	private:
		GODOT_CLASS(RoomStats, Node2D);
		String type = "room";
		Array enemies = {};
	public:
		static void _register_methods();
		void _init();
		void _ready();
		String _get_type();
		Array _get_enemies();
		RoomStats();
		~RoomStats();
	};
}