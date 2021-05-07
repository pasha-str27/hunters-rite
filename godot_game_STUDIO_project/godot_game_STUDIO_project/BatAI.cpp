#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::BatAI::BatAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2)
{
	enemy = node_tmp;
	can_move = true;
	speed = 100;

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();

	rng->randomize();

	if (rng->randi_range(0, 2))
	{
		current_goal = player2;
		current_player = "player2";
	}	
	else
	{
		current_goal = player1;
		current_player = "player1";
	}

	dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
}

void godot::BatAI::_add_bullet(Node* node)
{
}

void godot::BatAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::BatAI::reset_directions()
{
}

void godot::BatAI::change_direction()
{
}

void godot::BatAI::_remove_side(int dir)
{
}

void godot::BatAI::_change_dir_after_time()
{
}

void godot::BatAI::_fight(Node2D* player1, Node2D* player2)
{
}

void godot::BatAI::_delete_player1(Node2D* player1, Node2D* player2)
{
	if (current_player == String("player1") && player2 != nullptr)
	{
		enemy->call("_stop_timer");
		current_goal = player2;
		current_player = "player2";
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
		return;
	}

	RandomNumberGenerator* random = RandomNumberGenerator::_new();
	random->randomize();

	current_player = "";
	dir = (Vector2(random->randf_range(-100,100), random->randf_range(-100, 100))).normalized();
}

void godot::BatAI::_delete_player2(Node2D* player1, Node2D* player2)
{
	if (current_player == String("player2") && player1 != nullptr)
	{
		enemy->call("_stop_timer");
		current_goal = player1;
		current_player = "player1";
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
		return;
	}

	RandomNumberGenerator* random = RandomNumberGenerator::_new();
	random->randomize();

	current_player = "";
	dir = (Vector2(random->randf_range(-100, 100), random->randf_range(-100, 100))).normalized();
}

godot::String godot::BatAI::_get_current_player()
{
	return current_player;
}

void godot::BatAI::_set_speed(float value)
{
	speed = value;
}

void godot::BatAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	if(!enemy->call("_get_angry"))
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();

	if(dir.x < 0)
		cast_to<AnimatedSprite>(enemy->get_child(1)->get_child(0))->set_flip_h(false);
	else
		cast_to<AnimatedSprite>(enemy->get_child(1)->get_child(0))->set_flip_h(true);

	if (current_player == "")
	{
		RandomNumberGenerator* random = RandomNumberGenerator::_new();
		random->randomize();
		dir = (Vector2(random->randf_range(-100, 100), random->randf_range(-100, 100))).normalized();
	}

	cast_to<KinematicBody2D>(enemy)->move_and_slide(dir * speed);
}
