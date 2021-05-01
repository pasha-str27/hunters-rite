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
		speed = 100;
		enemy->call("_set_angry_on_code", false);
		current_goal = player2;
		current_player = "player2";
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
	}
}

void godot::BatAI::_delete_player2(Node2D* player1, Node2D* player2)
{
	if (current_player == String("player2") && player1 != nullptr)
	{
		speed = 100;
		enemy->call("_set_angry_on_code", false);
		current_goal = player1;
		current_player = "player1";
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
	}
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

	cast_to<KinematicBody2D>(enemy)->move_and_slide(dir * speed);
}
