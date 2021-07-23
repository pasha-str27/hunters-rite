#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class ItemsContainer;

	class ItemGenerator : public Node 
	{
	private:
		GODOT_CLASS(ItemGenerator, Node);

		ItemsContainer* items_container = nullptr;
		int count_to_spawn = 15;
		int current_count = 15;
	public:

		static void _register_methods();
		void _init();
		void _ready();
		void _dead_enemy(Vector2 enemy_position);
		int _get_count_to_spawn();
		void _set_count_to_spawn(int value);
		ItemGenerator* _get_instance();
		ItemGenerator();
		~ItemGenerator();
	};
}

