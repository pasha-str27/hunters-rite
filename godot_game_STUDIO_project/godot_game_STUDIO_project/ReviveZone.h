#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class ReviveZone :	public Area2D
	{
		GODOT_CLASS(ReviveZone, Area2D);

		std::vector<int> keys;
		RandomNumberGenerator *random;
		
		int current_key;

		Timer* timer;

		bool player_is_in_area;

	public:
		ReviveZone();
		~ReviveZone();
		static void _register_methods();
		void _init();
		void _ready();
		void _process();
		void _input(Input* event);
		void _on_revive_zone_body_entered(Node* node);
		void _on_revive_zone_body_exited(Node* node);
		int _generate_key();
		void _kill_revive_progress();
	};
}
