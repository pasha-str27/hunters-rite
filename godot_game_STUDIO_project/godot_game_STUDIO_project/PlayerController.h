#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerController : public KinematicBody2D
	{
	private:
		GODOT_CLASS(PlayerController, KinematicBody2D);
		IPlayer* current_player;
		Ref<PackedScene> bullet_prefab;

		float speed;
		Timer* timer;

	public:
		static void _register_methods();
		PlayerController();
		~PlayerController();
		void _init();
		void _input(Input* event);
		void _ready();
		void _start_timer();
		void _on_timeout();
		bool _can_fight();
		void _set_enemy(Node* enemy = nullptr);
		void _add_bullet(Node* node);
		void _process(float delta);
		void _take_damage(float damage);
		void _on_Area2D_body_entered(Node* node);
	};
}
