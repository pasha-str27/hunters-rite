#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Bullet : public KinematicBody2D
	{
	private:
		GODOT_CLASS(Bullet, KinematicBody2D);

		Vector2 dir;
		float speed;
		bool is_active;
		float damage;
		bool is_enemy_bullet;

	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _on_Area2D_body_entered(Node* node);
		void _process(float delta);
		void _set_dir(Vector2 dir);
		void _set_damage(float value);
		Bullet();
		~Bullet();
	};
}