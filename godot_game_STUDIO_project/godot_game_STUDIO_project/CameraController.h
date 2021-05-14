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

		Ref<PackedScene> fadeIn = nullptr;
		Ref<PackedScene> fadeOut = nullptr;
		Ref<PackedScene> game_back = nullptr;

		AudioStreamPlayer2D* audio = nullptr;
		Timer* timer_audio;

		float time_delta = 1.0 / 50;
		float delta_step = -80.0 / 50.0;

		void _move(String dir);
		String _get_dir_on_index(int i);
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		void _door_collision(String door_dir);
		void _open_doors();
		void _close_doors();
		void _start_move();
		void _change_audio_volume();
		CameraController();
		~CameraController();
	};
}
