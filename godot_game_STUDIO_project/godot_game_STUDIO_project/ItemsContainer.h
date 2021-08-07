#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class ItemsContainer: public Node
	{
	private:
		GODOT_CLASS(ItemsContainer, Node);
		Array items = {};
	public:
		static void _register_methods();
		void _init();
		void _ready();
		ItemsContainer* _get_instance();
		void _spawn_random_item(Vector2 pos);
		Array _get_items();
		ItemsContainer();
		~ItemsContainer();
	};
}
