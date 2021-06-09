#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif
namespace godot {
	class Key: public Node2D
	{
	private:
		GODOT_CLASS(Key, Node2D);
		String key_type;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		String _get_type();
		void _on_Area2D_body_entered(Node* node);
		Key();
		~Key();
	};
}