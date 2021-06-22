#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BigStone : public KinematicBody2D
	{
		GODOT_CLASS(BigStone, KinematicBody2D);

		int players_count = 0;
		Timer* timer = nullptr;
		bool can_heal = true;
		float heal_cooldown = 30;

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _remove_player(Node2D* node);
		void _add_player(Node2D* node);
		void _heal_players();
		void _can_heal_true();
		void _heal_player(Node2D* player);
	};
}