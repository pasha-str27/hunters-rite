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

		void _move(String dir);
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		void _input(InputEvent* event);
		void _door_collision(String door_dir);
		CameraController();
		~CameraController();
	};
}
