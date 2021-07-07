#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif
namespace godot {
	class CameraShake: public Node
	{
	private: 
		GODOT_CLASS(CameraShake, Node);
		Camera2D* camera = nullptr;

		float shake_power = 4;
		float  shake_time = 0.4;
		bool isShake = false;
		Vector2 curPos;
		float elapsedtime = 0;
	public:
		CameraShake();
		~CameraShake();
		static void _register_methods();
		void _init();
		void _ready();
		void _start(float power, float duration);
		void _process(float delta);
		void _shake(float delta);
	};
}


