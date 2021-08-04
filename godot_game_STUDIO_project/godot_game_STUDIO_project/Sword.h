#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Sword : public Area2D
	{
		GODOT_CLASS(Sword, Area2D);


	public:

		static void _register_methods();
		~Sword();
		void _init();
		void _on_Area2D_body_entered(Node* node);
		void _on_Area2D_body_exited(Node* node);
	};
}