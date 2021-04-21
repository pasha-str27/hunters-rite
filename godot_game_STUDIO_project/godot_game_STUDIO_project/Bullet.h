#pragma once
#include <KinematicBody2D.hpp>
#include <Godot.hpp>

namespace godot
{
	class Bullet : public KinematicBody2D
	{
	private:
		GODOT_CLASS(Bullet, KinematicBody2D);

		Vector2 dir;
		float speed;
		bool is_active;

	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _on_Area2D_body_entered(Node* node);
		void _process(float delta);
		void set_dir(Vector2 dir);
		Bullet();
		~Bullet();
	};
}