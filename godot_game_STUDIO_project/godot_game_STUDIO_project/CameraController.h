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

		void _move(String dir);
		String _get_dir_on_index(int i);
		bool _is_one_player_alive();
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		void _door_collision(String door_dir);
		void _open_doors();
		void _close_doors();
		void _start_move();
		CameraController();
		~CameraController();
	};
}
