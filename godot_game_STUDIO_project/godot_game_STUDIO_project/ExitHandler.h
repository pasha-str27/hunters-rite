#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class AudioController;

	class ExitHandler: public Node2D
	{
	private:
		GODOT_CLASS(ExitHandler, Node2D);
		Ref<PackedScene> fade_out = nullptr;
		int players_count = 0;
		Timer* timer = nullptr;
		Timer* timer_audio = nullptr;
		Timer* timer_music_out = nullptr;
		AudioServer* audio_server = nullptr;
		bool is_spawned = false;
		AudioController* audio_controller = nullptr;
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
		void _try_to_change_player_moving(Node2D* player, bool value);
		void _spawn_fade_out();
		ExitHandler();
		~ExitHandler();
	};
}