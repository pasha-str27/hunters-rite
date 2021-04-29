////#include <Godot.hpp>
////#include <Area2D.hpp>
////#include "Room.h"
//
//#ifndef HEADERFILE_H
//#define HEADERFILE_H
//#include "headers.h"
//#endif
//
//
//namespace godot {
//	class Door: public Area2D
//	{
//	private:
//		GODOT_CLASS(Door, Area2D);
//		bool correct_colliding = false;
//		Room* room_ref = nullptr;
//		Timer* timer = nullptr;
//	public:
//		String direction;
//
//		static void _register_methods();
//		void _init();
//		void _ready();
//		bool _get_correct_colliding();
//		void _check_correct_placing();
//		void _on_Area2D_area_entered(Node* other);
//		void _on_Area2D_area_exited(Node* other);
//		Door();
//		~Door();
//	};
//}
//
//
