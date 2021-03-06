#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class ExitHandler: public Node2D
	{
	private:
		GODOT_CLASS(ExitHandler, Node2D);
		Ref<PackedScene> fade_out = nullptr;
		Ref<PackedScene> menu_scene = nullptr;
		int players_count = 0;
		Timer* timer = nullptr;
		Timer* timer_audio = nullptr;
		Timer* timer_music_out = nullptr;
		AudioServer* audio_server = nullptr;
		bool is_spawned = false;
	public:

		static void _register_methods();
		void _init();
		void _ready();
		void _on_Area2D_area_entered(Node* other);
		void _on_Area2D_area_exited(Node* other);
		void _load_menu_scene();
		void _show_exit();
		void _mute_audio();
		void _audio_fade_to_main_menu();
		void _move_to_main_menu();
		ExitHandler();
		~ExitHandler();
	};
}