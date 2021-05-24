#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

Vector2 godot::SlimeAI::directions_swich(int value)
{
	float d = .5f;
	Vector2 direction;

	switch (value)
	{
	case 1:
		return Vector2(0, -d);
	case 2:
		cast_to<AnimatedSprite>(_get_enemy()->get_child(1)->get_child(0))->set_flip_h(false);
		return Vector2(-d, 0);
	case 3:
		cast_to<AnimatedSprite>(_get_enemy()->get_child(1)->get_child(0))->set_flip_h(true);
		return Vector2(d, 0);
	case 4:
		return Vector2(0, d);
	default:
		return Vector2();
	}
}

void godot::SlimeAI::_set_speed(float value)
{
	speed = value;
}

void godot::SlimeAI::_set_is_player1_onArea(bool value)
{
	is_player1_onArea = value;
}

void godot::SlimeAI::_set_is_player2_onArea(bool value)
{
	is_player2_onArea = value;
}

godot::SlimeAI::SlimeAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	can_move = true;
	is_cheking = false;
	speed = 400;

	old_pos = _get_enemy()->get_global_position();

	change_direction();
}

void godot::SlimeAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::SlimeAI::reset_directions()
{
	directions.clear();
}

void godot::SlimeAI::change_direction()
{
	reset_directions();

	for (int i = 2; i < 6; ++i)
	{
		if ((int)_get_enemy()->get_child(i)->call("_get_side") != -1 && _get_enemy()->get_child(i)->call("_get_current_node") != nullptr
			&& cast_to<Node2D>(_get_enemy()->get_child(i)->call("_get_current_node"))->is_in_group("player")
			&& (bool)cast_to<Node2D>(_get_enemy()->get_child(i)->call("_get_current_node"))->call("_is_alive"))
		{
			dir = directions_swich(i - 1);
			is_cheking = false;
			return;
		}

		if (!_get_enemy()->get_child(i)->call("_get_on_body"))
			directions.push_back(i - 1);
	}

	_change_dir_after_time();
}

void godot::SlimeAI::_remove_side(int dir)
{
	directions.push_back(dir);
}

void godot::SlimeAI::_change_dir_after_time()
{
	if (directions.size() == 0)
	{
		dir = Vector2::ZERO;
		return;
	}	

	RandomNumberGenerator* rand = RandomNumberGenerator::_new();
	rand->randomize();

	is_cheking = false;

	dir = directions_swich(directions[rand->randi_range(0, directions.size() - 1)]);
}

void godot::SlimeAI::_fight(Node2D* player1, Node2D* player2)
{
	can_move = false;

	if (is_player1_onArea && player1 != nullptr)
		player1->call("_take_damage", damage, false);

	if (is_player2_onArea && player2 != nullptr)
		player2->call("_take_damage", damage, false);

	_get_enemy()->call("_start_timer");
}

void godot::SlimeAI::_process(float delta)
{
	if (!can_move)
		return;

	_get_enemy()->set_global_position(_get_enemy()->get_global_position() + dir * delta * 235);

	if (is_cheking)
		return;

	if ((abs(old_pos.distance_to(_get_enemy()->get_global_position())-32) <= 3
		&&(dir==Vector2(0.5,0)|| dir == Vector2(-0.5, 0)|| dir == Vector2(0, 0.5)|| dir == Vector2(0, -0.5))
			|| (abs(old_pos.distance_to(_get_enemy()->get_global_position()) - sqrt(32*32+32*32)) <= 4.5
			&& (dir == Vector2(0.5, 0.5) || dir == Vector2(-0.5, 0.5) || dir == Vector2(0.5, -0.5) || dir == Vector2(-0.5, -0.5)))))
	{
		is_cheking = true;
		_fight(_get_player1(), _get_player2());
		change_direction();
		old_pos = _get_enemy()->get_global_position();
		return;
	}
}