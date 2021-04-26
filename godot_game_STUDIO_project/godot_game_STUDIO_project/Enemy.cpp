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

	register_property<Enemy, float>("HP", &Enemy::HP, 99);
}

godot::Enemy::Enemy()
{
	ai = new EnemyAIContext;
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
		ai->_set_strategy(new FlowerAI);
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
		queue_free();
}
