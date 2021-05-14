#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::BatAI::BatAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	can_move = true;
	speed = 100;

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();

	rng->randomize();

	if (PlayersContainer::_get_instance()->_players_count() == 2)
	{

		if (rng->randi_range(0, 2))
		{
			current_goal = PlayersContainer::_get_instance()->_get_player2();
			current_player = "player2";
		}
		else
		{
			current_goal = PlayersContainer::_get_instance()->_get_player1();
			current_player = "player1";
		}
	}
	else 
	{
		if (PlayersContainer::_get_instance()->_get_player2() == nullptr) {
			current_goal = PlayersContainer::_get_instance()->_get_player1();
			current_player = "player1";
		}
		else
		{
			current_goal = PlayersContainer::_get_instance()->_get_player2();
			current_player = "player2";
		}
	}

	dir = (current_goal->get_global_position() - _get_enemy()->get_global_position()).normalized();
}

void godot::BatAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::BatAI::_delete_player1()
{
	if (current_player == String("player1") && _get_player2() != nullptr)
	{
		_get_enemy()->call("_stop_timer");
		current_goal = _get_player2();
		current_player = "player2";
		dir = (current_goal->get_global_position() - _get_enemy()->get_global_position()).normalized();
		return;
	}

	//RandomNumberGenerator* random = RandomNumberGenerator::_new();
	//random->randomize();

	//current_player = "";
	//dir = (Vector2(random->randf_range(-100,100), random->randf_range(-100, 100))).normalized();
}

void godot::BatAI::_delete_player2()
{
	if (current_player == String("player2") && _get_player1() != nullptr)
	{
		_get_enemy()->call("_stop_timer");
		current_goal = _get_player1();
		current_player = "player1";
		dir = (current_goal->get_global_position() - _get_enemy()->get_global_position()).normalized();
		return;
	}

	/*RandomNumberGenerator* random = RandomNumberGenerator::_new();
	random->randomize();

	current_player = "";
	dir = (Vector2(random->randf_range(-100, 100), random->randf_range(-100, 100))).normalized();*/
}


godot::String godot::BatAI::_get_current_player()
{
	return current_player;
}

void godot::BatAI::_set_speed(float value)
{
	speed = value;
}

void godot::BatAI::_process(float delta)
{
	if (!can_move)
		return; 

	if(!_get_enemy()->call("_get_angry"))
		dir = (current_goal->get_global_position() - _get_enemy()->get_global_position()).normalized();

	if(dir.x < 0)
		cast_to<AnimatedSprite>(_get_enemy()->get_child(1)->get_child(0))->set_flip_h(false);
	else
		cast_to<AnimatedSprite>(_get_enemy()->get_child(1)->get_child(0))->set_flip_h(true);

	if (current_player == "")
	{
		RandomNumberGenerator* random = RandomNumberGenerator::_new();
		random->randomize();
		dir = (Vector2(random->randf_range(-100, 100), random->randf_range(-100, 100))).normalized();
	}

	cast_to<KinematicBody2D>(_get_enemy())->move_and_slide(dir * speed);
}
