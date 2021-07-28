#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class AudioController;

	class GameManager : public Camera2D
	{
		GODOT_CLASS(GameManager, Camera2D);

		Node2D* player1;
		Node2D* player2;
		Array dirs = {};	//	0 - left, 1 - right, 2 - top, 3 - bottom
		bool is_open_door = true;
		bool is_showing_minimap = false;
		String current_room_type = "";

		Ref<PackedScene> fadeIn = nullptr;
		Ref<PackedScene> fadeOut = nullptr;
		Ref<PackedScene> game_back = nullptr;
		Ref<PackedScene> boss_back = nullptr;
		Ref<PackedScene> pause_menu = nullptr;
		Ref<PackedScene> exit = nullptr;

		CanvasItem* minimap = nullptr;

		AudioStreamPlayer2D* audio = nullptr;
		AudioStreamPlayer2D* audio_boss = nullptr;
		Timer* timer_audio;

		float time_delta = 1.0 / 50;
		float delta_step = -80.0 / 50.0;

		float horizontal_delta = 1024;
		float vertical_delta = 720;

		Array generated_keys = {};
		AudioController* audio_controller = nullptr;

		void _move(String dir);
		String _get_dir_on_index(int i);
		bool _is_one_player_alive();

	public:
		static int current_level;

		static void _register_methods();
		void _init();
		void _ready();
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
		void _create_keys_holders();
		bool _is_player_have_need_keys(Color rooms_key);
		void _show_game_over_screen();
		GameManager();
		~GameManager();
	};
}