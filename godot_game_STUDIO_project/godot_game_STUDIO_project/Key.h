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
		Color key_color;
		HBoxContainer* key_box = nullptr;
		Ref<PackedScene> particles = nullptr;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		String _get_type();
		Color _get_color();
		void _on_Area2D_body_entered(Node* node);
		void _make_sound();
		void _spawn_particles();
		Key();
		~Key();
	};
}