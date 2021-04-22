#pragma once
#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot {
	class SpawnPointChecker: public Area2D
	{
	private:
		GODOT_CLASS(SpawnPointChecker, Area2D);
	public:

		static void _register_methods();
		void _init();
		void _on_SpawnPointChecker_area_entered(Node* other);
	};
}


