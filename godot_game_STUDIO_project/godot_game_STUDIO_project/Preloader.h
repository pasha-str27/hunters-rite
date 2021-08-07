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
		AudioStreamPlayer2D* audio = nullptr;

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _load_menu();
		void _play_logo_sound();
		void _play_sound(Ref<AudioStream>);
		void _stop_sounds();
		void load();
		Preloader();
		~Preloader();
	};
}
