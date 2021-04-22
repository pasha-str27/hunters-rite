#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::Bullet::_register_methods()
{
	register_method("_process", &Bullet::_process);
	register_method("_ready", &Bullet::_ready);
	register_method("_init", &Bullet::_init);
	register_method("_on_Area2D_body_entered", &Bullet::_on_Area2D_body_entered);
	register_method("_set_dir", &Bullet::_set_dir);

	register_property<Bullet, Vector2>("direction", &Bullet::dir, Vector2(5, 5));
	register_property<Bullet, float>("speed", &Bullet::speed, 10);
	register_property<Bullet, float>("damage", &Bullet::damage, 10);
}

void godot::Bullet::_ready()
{
}

void godot::Bullet::_init()
{
}

void godot::Bullet::_on_Area2D_body_entered(Node* node)
{
	if (node->get_name().find("Enemy") != -1)
		node->call("_take_damage", 10);

	get_node("/root/Node2D/Player1")->call("_add_bullet", this);
}

void godot::Bullet::_process(float delta)
{
	if(is_visible())
		move_and_slide(dir*speed);
}

void godot::Bullet::_set_dir(Vector2 dir)
{
	this->dir = dir;
}

godot::Bullet::Bullet()
{
	is_active = false;
	dir = Vector2(0, 0);
	damage = 10;
}

godot::Bullet::~Bullet()
{
}
