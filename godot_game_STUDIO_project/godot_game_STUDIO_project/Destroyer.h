#pragma once
#include <Godot.hpp>
#include <Area2D.hpp>
namespace godot {
	class Destroyer: public Area2D
	{
	private:
		GODOT_CLASS(Destroyer, Area2D);
	public:

		void _init();
		void _ready();
		static void _register_methods();
		void _on_Destroyer_area_entered(Node* other);
		Destroyer();
		~Destroyer();
	};
}


