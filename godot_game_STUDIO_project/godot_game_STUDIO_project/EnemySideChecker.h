#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class EnemySideChecker : public Area2D
	{
		GODOT_CLASS(EnemySideChecker, Area2D);
		int side;
		bool is_in_boby;
		Node2D* current_node;

	public:
		static void _register_methods();
		void _on_Area2D_body_entered(Node2D* node);
		void _on_Area2D_body_exited(Node2D* node);
		void _init();
		bool _get_on_body();
		void _ready();
		Node2D* _get_current_node();
		Vector2 directions_swich(int value);
	};
}
