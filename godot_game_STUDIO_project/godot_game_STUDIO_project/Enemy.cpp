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
	register_method("_remove_player1", &Enemy::_remove_player1);
	register_method("_remove_player2", &Enemy::_remove_player2);
	register_method("_remove_side", &Enemy::_remove_side);
	register_method("_change_dir_after_time", &Enemy::_change_dir_after_time);
	register_method("_start_timer_for_dir_change", &Enemy::_start_timer_for_dir_change);
	register_method("_on_Area2D_body_entered", &Enemy::_on_Area2D_body_entered);
	register_method("_set_angry", &Enemy::_set_angry);
	register_method("_set_angry_on_code", &Enemy::_set_angry_on_code);
	register_method("_get_angry", &Enemy::_get_angry);
	register_method("_stop_timer", &Enemy::_stop_timer);
	register_method("_change_angry_on_timeout", &Enemy::_change_angry_on_timeout);
	
	register_property<Enemy, Ref<PackedScene>>("bullet", &Enemy::bullet, nullptr);
	register_property<Enemy, float>("HP", &Enemy::HP, 99);
}

godot::Enemy::Enemy()
{
	ai = new EnemyAIContext;
	entered = false;
	timer = Timer::_new();
	timer_change_dir = Timer::_new();
	HP = 100;
	is_angry = false;
	died = false;
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

	if (is_in_group("flower"))
	{
		ai->_set_strategy(new FlowerAI(bullet, this));
		return;
	}
		
	if (is_in_group("spider"))
	{
		ai->_set_strategy(new SpiderAI(bullet, this));
		return;
	}

	if (is_in_group("slime"))
	{
		ai->_set_strategy(new SlimeAI(bullet, this));
		return;
	}

	if (is_in_group("bat"))
	{
		ai->_set_strategy(new BatAI(bullet, this, ai->get_player1(), ai->get_player2()));
		return;
	}
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
		died = true;
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

	if(is_visible())
		ai->change_can_fight(true);
}

void godot::Enemy::_destroy_enemy()
{
	auto health_bar = cast_to<ProgressBar>(get_child(0));
	if (health_bar != nullptr)
		health_bar->set_value(HP);


	timer->disconnect("timeout", this, "_destroy_enemy");
	Enemies::get_singleton()->_remove_enemy(this);

	if(is_in_group("flower"))
		get_node("/root/Node2D/Node/BulletConteinerFlower")->queue_free();

	if (is_in_group("spider"))
		get_node("/root/Node2D/Node/BulletConteinerSpider")->queue_free();

	queue_free();
}

void godot::Enemy::_remove_player1()
{
	ai->_delete_player1();
}

void godot::Enemy::_remove_player2()
{
	ai->_delete_player2();
}

void godot::Enemy::_remove_side(int side)
{
	ai->_remove_side(side);
}

void godot::Enemy::_start_timer_for_dir_change()
{
	if (!timer_change_dir->is_connected("timeout", this, "_change_dir_after_time"))
	{
		timer_change_dir->connect("timeout", this, "_change_dir_after_time");
		timer_change_dir->start(0.01);
	}
}

void godot::Enemy::_on_Area2D_body_entered(Node* node)
{
	float damage = 20;
	if (is_angry)
		damage = 30;

	if (node->is_in_group("player") && !died)
		node->call("_take_damage", damage, false);
}

void godot::Enemy::_set_angry(Node* node)
{
	if (node->is_in_group(ai->_get_current_player()))
	{
		if (!entered && !is_angry)
		{
			ai->_set_speed(0);
			entered = true;
			if (!timer_change_dir->is_connected("timeout", this, "_change_angry_on_timeout"))
			{
				timer_change_dir->connect("timeout", this, "_change_angry_on_timeout");
				timer_change_dir->start(1);
			}
			return;
		}

		_stop_timer();
	}
}

void godot::Enemy::_set_angry_on_code(bool value)
{
	is_angry = value;
}

void godot::Enemy::_change_angry_on_timeout()
{
	timer_change_dir->disconnect("timeout", this, "_change_angry_on_timeout");
	ai->_set_speed(200);
	is_angry = true;
}

bool godot::Enemy::_get_angry()
{
	return is_angry;
}

void godot::Enemy::_stop_timer()
{
	ai->_set_speed(100);
	is_angry = false;
	entered = false;

	if (timer_change_dir->is_connected("timeout", this, "_change_angry_on_timeout"))
	{
		timer_change_dir->stop();
		timer_change_dir->disconnect("timeout", this, "_change_angry_on_timeout");
	}
}

void godot::Enemy::_change_dir_after_time()
{
	timer_change_dir->disconnect("timeout", this, "_change_dir_after_time");
	ai->_change_dir_after_time();
}