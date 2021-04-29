#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::Enemy::_register_methods()
{
	register_method("_ready", &Enemy::_ready);
	register_method("_init", &Enemy::_init);
	register_method("_process", &Enemy::_process);
	register_method("_take_damage", &Enemy::_take_damage);
	register_method("_add_bullet", &Enemy::_add_bullet);
	register_method("_on_timeout", &Enemy::_on_timeout);
	register_method("_start_timer", &Enemy::_start_timer);
	register_method("_update_health_bar", &Enemy::_update_health_bar);

	register_property<Enemy, Ref<PackedScene>>("bullet", &Enemy::bullet, nullptr);
	register_property<Enemy, float>("HP", &Enemy::HP, 100);
}

godot::Enemy::Enemy()
{
	ai = new EnemyAIContext;
	timer = Timer::_new();
	timer_change_dir = Timer::_new();
	HP = 100;
}

godot::Enemy::~Enemy()
{
}

void godot::Enemy::_init()
{
}

void godot::Enemy::_ready()
{
	ai->set_enemy(this);
	ai->set_player1(cast_to<Node2D>(get_node("/root/Node2D/Node/Player1")));
	ai->set_player2(cast_to<Node2D>(get_node("/root/Node2D/Node/Player2")));

	Enemies::get_singleton()->_add_enemy(this);

	add_child(timer_change_dir);
	add_child(timer);
	_update_health_bar();
}

void godot::Enemy::_process(float delta)
{
	//ai->_process(delta);
}

void godot::Enemy::_take_damage(float damage)
{
	HP -= damage;

	Godot::print("taking");

	_update_health_bar();

	if (HP <= 0)
	{
		Enemies::get_singleton()->_remove_enemy(this);
		get_child(0)->queue_free();
		set_visible(false);
		ai->change_can_fight(false);

		timer->connect("timeout", this, "_destroy_enemy");

		timer->set_wait_time(10);
		timer->start();
	}		
}

void godot::Enemy::_add_bullet(Node *bullet)
{
	ai->_add_bullet(bullet);
}

void godot::Enemy::_start_timer()
{
	if (!timer->is_connected("timeout", this, "_on_timeout"))
	{
		timer->connect("timeout", this, "_on_timeout");

		timer->start(0.65);
	}
}

void godot::Enemy::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	ai->change_can_fight(true);
}

void godot::Enemy::_update_health_bar()
{
	auto health_bar = cast_to<ProgressBar>(get_child(0));
	if (health_bar != nullptr)
		health_bar->set_value(HP);
}