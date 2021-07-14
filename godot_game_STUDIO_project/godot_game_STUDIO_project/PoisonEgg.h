#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif


namespace godot {
	class PoisonEgg: public Node2D
	{
	private:
		GODOT_CLASS(PoisonEgg, Node2D);
		
		Ref<PackedScene> destroy_particles;
		Particles2D* start_particles;
		Timer* timer;

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_timer_out();
		void _on_player_area_entered(Node* node);
		void _make_destroy_particles();
		PoisonEgg();
		~PoisonEgg();
	};
}


