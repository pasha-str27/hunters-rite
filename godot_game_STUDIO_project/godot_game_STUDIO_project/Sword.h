#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Sword : public Area2D
	{
		GODOT_CLASS(Sword, Area2D);

		float damage;

	public:

		static bool is_enemy_on_sword;

		static void _register_methods();
		Sword();
		~Sword();
		void _init();
		void _ready();
		void _process();
		void _on_Area2D_body_entered(Node* node);
		void _on_Area2D_body_exited(Node* node);
	};
}