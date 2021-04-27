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
	register_method("_destroy_enemy", &Enemy::_destroy_enemy);


	register_property<Enemy, Ref<PackedScene>>("bullet", &Enemy::bullet, nullptr);
	register_property<Enemy, float>("HP", &Enemy::HP, 99);
}

godot::Enemy::Enemy()
{
	ai = new EnemyAIContext;
	timer = Timer::_new();
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
	if(is_in_group("flower"))
		ai->_set_strategy(new FlowerAI(bullet, this));
	else
		ai->_set_strategy(new SimpleEnemyAI);

	ai->set_enemy(this);
	ai->set_player1(cast_to<Node2D>(get_node("/root/Node2D/Node/Player1")));
	ai->set_player2(cast_to<Node2D>(get_node("/root/Node2D/Node/Player2")));
}

void godot::Enemy::_process(float delta)
{
	ai->_process(delta);
}

void godot::Enemy::_take_damage(float damage)
{
	HP -= damage;

	if (HP <= 0)
	{
		get_child(0)->queue_free();
		set_visible(false);
		ai->change_can_fight(false);

		timer->connect("timeout", this, "_destroy_enemy");

		if (!has_node(NodePath(timer->get_name())))
		{
			add_child(timer);
		}

		timer->set_wait_time(1.5f);
		timer->start();
	}		
}

void godot::Enemy::_add_bullet(Node *bullet)
{
	ai->_add_bullet(bullet);
}

void godot::Enemy::_start_timer()
{
	timer->connect("timeout", this, "_on_timeout");

	if (!has_node(NodePath(timer->get_name())))
	{
		add_child(timer);
	}

	timer->set_wait_time(1.4f);
	timer->start();
}

void godot::Enemy::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	if(is_visible())
		ai->change_can_fight(true);
}

void godot::Enemy::_destroy_enemy()
{
	timer->disconnect("timeout", this, "_destroy_enemy");
	queue_free();
}
