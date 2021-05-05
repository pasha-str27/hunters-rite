#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

#include <AnimationPlayer.hpp>

namespace godot
{
	class Item : public Node2D
	{
		GODOT_CLASS(Item, Node2D);

		AnimationPlayer* animator = nullptr;

		float speed;
		float HP;
		float damage;
		bool decrease_attack_radius;
		bool encrease_attack_radius;
		int number_to_next_item;
		float attack_speed_delta;
		bool is_buff = true;

	public:
		static void _register_methods();
		Item();
		~Item();
		void _ready();
		void _init();
		void _process();
		void _on_Area2D_body_entered(Node* node);
		bool _get_is_buff();
	};
}