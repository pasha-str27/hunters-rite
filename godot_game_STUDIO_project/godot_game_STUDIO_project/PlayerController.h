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

	public:
		static void _register_methods();
		PlayerController();
		~PlayerController();
		void _init();
		void _input(Input* event);
		void _ready();
		void add_bullet(Node* node);
		void _process(float delta);
	};
}
