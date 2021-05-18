#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Bullet::_register_methods()
{
	register_method("_process", &Bullet::_process);
	register_method("_ready", &Bullet::_ready);
	register_method("_init", &Bullet::_init);
	register_method("_on_Area2D_body_entered", &Bullet::_on_Area2D_body_entered);
	register_method("_set_dir", &Bullet::_set_dir);
	register_method("_set_damage", &Bullet::_set_damage);
	
	register_property<Bullet, Vector2>("direction", &Bullet::dir, Vector2(5, 5));
	register_property<Bullet, float>("speed", &Bullet::speed, 10);
	register_property<Bullet, float>("damage", &Bullet::damage, 10);
	register_property<Bullet, Ref<PackedScene>>("Explosion Particles", &Bullet::explosion_particles, nullptr);
}

void godot::Bullet::_ready()
{
	cast_to<AnimationPlayer>(get_child(0)->get_child(0)->get_child(0))->set_current_animation("idle");
}

void godot::Bullet::_init()
{
}

void godot::Bullet::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("player") && !node->call("_is_alive"))
		return;

	if (!is_visible())
		return;

	cast_to<Node2D>(this)->set_visible(false);
	if (explosion_particles != nullptr)
	{
		auto particles = cast_to<Node2D>(explosion_particles->instance());
		particles->set_global_position(this->get_global_position());
		get_node("/root/Node2D/Node")->add_child(particles);
	}

	if (node->is_in_group("player") && is_in_group("web_bullet")) 
	{
		node->call("_change_can_moving", false);
		node->call("_animate_spider_web");
	}
	else
	{
		if (node->is_in_group("enemy"))
			node->call("_take_damage", damage, 1);

		if (node->is_in_group("player"))
			node->call("_take_damage", damage, false);
	}

	if (is_in_group("statue_bullet") || is_in_group("web_bullet") || is_in_group("player_bullet") || is_in_group("flower_bullet"))
		get_parent()->get_parent()->get_child(1)->call("_add_bullet", this);
}

void godot::Bullet::_process(float delta)
{
	if (is_visible())
		move_and_slide(dir * speed);	
}

void godot::Bullet::_set_dir(Vector2 dir)
{
	this->dir = dir;
}

void godot::Bullet::_set_damage(float value)
{
	damage = value;
}

godot::Bullet::Bullet()
{
	is_active = false;
	is_enemy_bullet = false;
	dir = Vector2(0, 0);
	damage = 25;
	speed = 250;
}

godot::Bullet::~Bullet()
{
}
