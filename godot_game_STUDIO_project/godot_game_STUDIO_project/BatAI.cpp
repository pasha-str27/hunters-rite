#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::BatAI::BatAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2)
{
	enemy = node_tmp;
	can_move = true;

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
		current_goal = player2;
		current_player = "player2";
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
	}
}

void godot::BatAI::_delete_player2(Node2D* player1, Node2D* player2)
{
	if (current_player == String("player2") && player1 != nullptr)
	{
		current_goal = player1;
		current_player = "player1";
		dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();
	}
}

void godot::BatAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	if (!can_move)
		return;

	if (current_goal == nullptr)
		Godot::print("error");


	dir = (current_goal->get_global_position() - enemy->get_global_position()).normalized();

	cast_to<KinematicBody2D>(enemy)->move_and_slide(dir * 100);
}
