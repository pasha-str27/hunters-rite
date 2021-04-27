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

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		void _input(InputEvent* event);
		CameraController();
		~CameraController();
	};
}
