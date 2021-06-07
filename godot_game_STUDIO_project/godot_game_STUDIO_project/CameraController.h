#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class CameraController : public Camera2D
	{
		GODOT_CLASS(CameraController, Camera2D);

		Node2D* player1;
		Node2D* player2;
		Array dirs = {};	//	0 - left, 1 - right, 2 - top, 3 - bottom
		bool is_open_door = true;
		String current_room_type = "";

		Ref<PackedScene> fadeIn = nullptr;
		Ref<PackedScene> fadeOut = nullptr;
		Ref<PackedScene> game_back = nullptr;
		Ref<PackedScene> boss_back = nullptr;
		Ref<PackedScene> pause_menu = nullptr;
		Ref<PackedScene> exit = nullptr;

		static Node2D* current_room;

		AudioStreamPlayer2D* audio = nullptr;
		AudioStreamPlayer2D* audio_boss = nullptr;
		Timer* timer_audio;
		AudioServer* audio_server = nullptr;

		float time_delta = 1.0 / 50;
		float delta_step = -80.0 / 50.0;

		void _move(String dir);
		String _get_dir_on_index(int i);
		bool _is_one_player_alive();
	public:
		static Node2D* current_room;

		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		void _door_collision(String door_dir);
		void _open_doors();
		void _close_doors();
		void _start_move();
		void _change_audio_volume();
		void _mute_audio_volume();
		void _start_mute_volume();
		void _input(Variant event);
		void _audio_fade_to_main_menu();
		void _spawn_exit();
		void _set_current_room_type(String);
		void _go_to_start();
		void _spawn_players();
		CameraController();
		~CameraController();
	};
}
