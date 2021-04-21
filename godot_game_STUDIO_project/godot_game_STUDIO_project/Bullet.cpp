#include "Bullet.h"

using namespace godot;

void godot::Bullet::_register_methods()
{
	register_method("_process", &Bullet::_process);
	register_method("_ready", &Bullet::_ready);
	register_method("_init", &Bullet::_init);
	register_method("_on_Area2D_body_entered", &Bullet::_on_Area2D_body_entered);
	register_method("set_dir", &Bullet::set_dir);

	register_property<Bullet, Vector2>("direction", &Bullet::dir, Vector2(5, 5));
	register_property<Bullet, float>("speed", &Bullet::speed, 10);
}

void godot::Bullet::_ready()
{
}

void godot::Bullet::_init()
{
}

void godot::Bullet::_on_Area2D_body_entered(Node* node)
{
	get_node("/root/Node2D/Player1")->call("add_bullet", this);
}

void godot::Bullet::_process(float delta)
{
	if(is_visible())
		move_and_slide(dir*speed);
}

void godot::Bullet::set_dir(Vector2 dir)
{
	this->dir = dir;
}

godot::Bullet::Bullet()
{
	is_active = false;
	dir = Vector2(0, 0);
}

godot::Bullet::~Bullet()
{
}
