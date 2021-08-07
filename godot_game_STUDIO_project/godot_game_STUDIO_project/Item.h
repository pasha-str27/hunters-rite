#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Item : public Node2D
	{
		GODOT_CLASS(Item, Node2D);

		AnimationPlayer* animator = nullptr;
		String name;
		float speed;
		float HP;
		float damage;
		int items_counter;
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
		void _on_Area2D_body_entered(Node* node);
		void _apply_item(Node* player);
		//	creating UI for items holders
		Control* _create_control();
		TextureRect* _create_item_sprite();
		TextureRect* _create_item_background(Ref<Texture>);
		Label* _create_text(Ref<Theme> theme);
	};
}