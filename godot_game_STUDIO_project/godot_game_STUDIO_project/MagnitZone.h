#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class MagnitZone : public Area2D
	{
		GODOT_CLASS(MagnitZone, Area2D);

		Node2D* player1 = nullptr;
		Node2D* player2 = nullptr;
		float force = 85;

		bool is_active;

	public:
		static void _register_methods();
		MagnitZone();
		~MagnitZone();
		void _init();
		void _ready();
		void _process(float delta);
		void _on_body_entered(Node* node);
		void _on_body_exited(Node* node);
		void _set_player1();
		void _set_player2();
		void _set_active(bool active);
	};
}
