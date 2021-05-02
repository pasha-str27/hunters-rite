#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Item : public Node2D
	{
		GODOT_CLASS(Item, Node2D);

		float speed;
		float HP;
		float damage;
		bool decrease_attack_radius;
		bool encrease_attack_radius;
		int number_to_next_item;
		float attack_speed_delta;

	public:
		static void _register_methods();
		Item();
		~Item();
		void _ready();
		void _init();
		void _process();
		void _on_Area2D_body_entered(Node* node);
	};
}