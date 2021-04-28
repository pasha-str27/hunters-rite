#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SpiderSide : public Area2D
	{
		GODOT_CLASS(SpiderSide, Area2D);
		int side;

	public:
		static void _register_methods();
		void _on_Area2D_body_entered(Node2D* node);
		void _init();
		void _ready();
	};
}
