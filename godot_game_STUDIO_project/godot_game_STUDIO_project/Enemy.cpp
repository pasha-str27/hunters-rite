#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

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
	register_method("_set_player1", &Enemy::_set_player1);
	register_method("_set_player2", &Enemy::_set_player2);
	register_method("_update_health_bar", &Enemy::_update_health_bar);
	register_method("_change_animation", &Enemy::_change_animation);
	register_method("_set_current_player", &Enemy::_set_current_player);
	register_method("_remove_current_player", &Enemy::_remove_current_player);
	register_method("_on_spawn_end", &Enemy::_on_spawn_end);
	
	
	register_property<Enemy, Ref<PackedScene>>("bullet", &Enemy::bullet, nullptr);
	register_property<Enemy, float>("HP", &Enemy::HP, 99);
	register_property<Enemy, Ref<PackedScene>>("Death particles", &Enemy::death_particles, nullptr);
}

godot::Enemy::Enemy()
{
	ai = new EnemyAIContext;
	entered = false;
	timer = Timer::_new();
	timer_change_dir = Timer::_new();
	timer_particles = Timer::_new();
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
	Enemies::get_singleton()->_add_enemy(this);
	
	_update_health_bar();

	add_child(timer_change_dir);
	add_child(timer);
	add_child(timer_particles);

	sp = cast_to<AnimatedSprite>(get_node("CollisionShape2D/AnimatedSprite"));
	spawn_particles = cast_to<Particles2D>(get_node("SpawnParticles"));

	if (is_in_group("flower"))
		ai->_set_strategy(new FlowerAI(bullet, this));
		
	if (is_in_group("spider"))
		ai->_set_strategy(new SpiderAI(bullet, this));

	if (is_in_group("slime"))
		ai->_set_strategy(new SlimeAI(bullet, this));

	if (is_in_group("bat"))
		ai->_set_strategy(new BatAI(bullet, this));

	if (is_in_group("statue_melee"))
		ai->_set_strategy(new StatueMeleeAI(bullet, this));

	if (is_in_group("statue_shoot"))
		ai->_set_strategy(new StatueShootAI(bullet, this));

	spawn_particles->set_emitting(true);
	timer_particles->connect("timeout", this, "_on_spawn_end");
	timer_particles->start(0.5f);
	cast_to<Node2D>(get_node("CollisionShape2D"))->set_visible(false);

	if(is_in_group("flower"))
		cast_to<ProgressBar>(get_parent()->get_node("BossHealthBar"))->set_visible(false);
	else
		cast_to<ProgressBar>(get_node("HealthBar"))->set_visible(false);
}

void godot::Enemy::_process(float delta)
{
	if (!can_move)
		return;

	if(!died)
		ai->_process(delta);

	if (sp != nullptr && !died) 
	{
		String animation_name = sp->get_animation();
		if (sp->get_sprite_frames()->get_animation_loop(animation_name) == false && sp->get_frame() == sp->get_sprite_frames()->get_frame_count(animation_name) - 1)
			sp->play("idle");
	}
}

void godot::Enemy::_take_damage(float damage, int player_id)
{
	if (HP <= 0 || !can_move)
		return;

	HP -= damage;
	_update_health_bar();

	if(sp != nullptr)
		sp->play("damaged");

	if (HP <= 0)
	{
		Node *player = nullptr;

		if (player_id == 1)
			player = CustomExtensions::GetChildByName(get_node("/root/Node2D/Node/Player1"), "Player1");
		else if(player_id == 2)
			player = CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Player2");

		player->call("_on_enemy_die", this->get_global_position());

		died = true;
		Enemies::get_singleton()->_remove_enemy(this);

		if(Enemies::get_singleton()->_get_enemies_count() == 0)
			CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->call("_open_doors");

		set_collision_layer_bit(2, false);
		set_collision_mask_bit(9, false);

		if (has_node("zone"))
			get_node("zone")->queue_free();

		get_child(0)->queue_free();
		set_visible(false);
		ai->change_can_fight(false);

		timer->connect("timeout", this, "_destroy_enemy");

		timer->start(1);
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

		timer->start(1);
	}
}

void godot::Enemy::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	if (is_visible())
		ai->change_can_fight(true);
}

void godot::Enemy::_destroy_enemy()
{
	_update_health_bar();

	timer->disconnect("timeout", this, "_destroy_enemy");
	Enemies::get_singleton()->_remove_enemy(this);

	get_parent()->queue_free();
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
		timer_change_dir->start((real_t)0.01);
	}
}

void godot::Enemy::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("player") && !died)
	{
		float damage = 20;
		if (is_angry)
			damage = 30;

		node->call("_take_damage", damage, false);
	}
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
	_change_animation("attack", 1.5f);
	timer_change_dir->disconnect("timeout", this, "_change_angry_on_timeout");

	cast_to<Particles2D>(get_node("BatDashParticles"))->restart();

	ai->_set_speed(200);
	is_angry = true;
}

void godot::Enemy::_set_player1(Node* player)
{
	ai->set_player1(cast_to<Node2D>(player));
}

void godot::Enemy::_set_player2(Node* player)
{
	ai->set_player2(cast_to<Node2D>(player));
}

bool godot::Enemy::_get_angry()
{
	return is_angry;
}

void godot::Enemy::_stop_timer()
{
	_change_animation("idle", 1);

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

void godot::Enemy::_update_health_bar()
{
	auto health_bar = cast_to<ProgressBar>(CustomExtensions::GetChildByName(this, "HealthBar"));

	if (health_bar == nullptr)
		health_bar = cast_to<ProgressBar>(CustomExtensions::GetChildByName(this->get_parent(), "BossHealthBar"));

	if (health_bar != nullptr)
		health_bar->set_value(HP);

}	

void godot::Enemy::_change_animation(String _name = "", float speed_scale = 1)
{
	
	if (_name == "" || sp == nullptr)
		return;

	if (_name == "stop")
	{
		sp->stop();
		return;
	}

	sp->play(_name);
	sp->set_speed_scale(speed_scale);
}

void godot::Enemy::_set_current_player(Node* node)
{
	if (node->is_in_group("player1"))
		ai->set_player1(cast_to<Node2D>(node));

	if (node->is_in_group("player2"))
		ai->set_player2(cast_to<Node2D>(node));
}

void godot::Enemy::_remove_current_player(Node* node)
{
	if (node->is_in_group("player1"))
		ai->_delete_player1();

	if (node->is_in_group("player2"))
		ai->_delete_player2();
}

void godot::Enemy::_on_spawn_end()
{
	timer_particles->disconnect("timeout", this, "_on_spawn_end");
	can_move = true;
	spawn_particles->set_emitting(false);
	cast_to<Node2D>(get_node("CollisionShape2D"))->set_visible(true);

	if (is_in_group("flower"))
		cast_to<ProgressBar>(get_parent()->get_node("BossHealthBar"))->set_visible(true);
	else
		cast_to<ProgressBar>(get_node("HealthBar"))->set_visible(true);
}
