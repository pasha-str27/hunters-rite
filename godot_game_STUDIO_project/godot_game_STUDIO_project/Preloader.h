#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class Preloader: public Node2D
	{
	private:
		GODOT_CLASS(Preloader, Node2D);
		Ref<PackedScene> menu_scene = nullptr;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _load_menu();
		void _play_logo_sound();
		Preloader();
		~Preloader();
	};
}


