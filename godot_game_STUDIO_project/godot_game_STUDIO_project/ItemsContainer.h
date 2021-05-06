#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class ItemsContainer: public Node
	{
	private:
		GODOT_CLASS(ItemsContainer, Node);
	public:
		Array items = {};

		static void _register_methods();
		void _init();
		void _ready();
		ItemsContainer* _get_instance();
		ItemsContainer();
		~ItemsContainer();
	};
}
