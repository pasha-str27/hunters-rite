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
	if (!is_visible())
		return;

	cast_to<Node2D>(this)->set_visible(false);

	if (node->is_in_group("player") && is_in_group("web_bullet"))
	{
		node->call("_change_can_moving", false);
	}
	else
	{
		if (node->is_in_group("enemy") || node->is_in_group("player"))
		{
			node->call("_take_damage", damage);
		}
	}

	if (is_in_group("flower_bullet"))
	{
		get_node("/root/Node2D/Node/flower")->call("_add_bullet", this);
	}

	if (is_in_group("web_bullet"))
	{
		get_node("/root/Node2D/Node/Spider")->call("_add_bullet", this);
	}

	if (is_in_group("player_bullet"))
	{
		get_node("/root/Node2D/Node/Player1")->call("_add_bullet", this);
	}
}

void godot::Bullet::_process(float delta)
{
	if (is_visible())
	{
		move_and_slide(dir * speed);
	}
		
}

void godot::Bullet::_set_dir(Vector2 dir)
{
	this->dir = dir;
}

godot::Bullet::Bullet()
{
	is_active = false;
	is_enemy_bullet = false;
	dir = Vector2(0, 0);
	damage = 25;
}

godot::Bullet::~Bullet()
{
}
