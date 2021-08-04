#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SillyBoyAI::_set_is_player1_onArea(bool value)
{
	is_player1_onArea = value;
	was_setted = true;
}

void godot::SillyBoyAI::_set_is_player2_onArea(bool value)
{
	is_player2_onArea = value;
	was_setted = true;
}

void godot::SillyBoyAI::_change_start_parameters()
{
	cur_pos = (_get_enemy()->get_global_position() -
		CurrentRoom::get_singleton()->_get_current_room()->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / _get_distance();

	old_pos = _get_enemy()->get_global_position();

	change_direction();
}

void godot::SillyBoyAI::_set_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_set_is_player1_onArea(true);

	if (player->is_in_group("player2"))
		_set_is_player2_onArea(true);
}

void godot::SillyBoyAI::_remove_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_delete_player1();

	if (player->is_in_group("player2"))
		_delete_player2();

	if (player->is_in_group("player1"))
		_set_is_player1_onArea(false);

	if (player->is_in_group("player2"))
		_set_is_player2_onArea(false);
}

void godot::SillyBoyAI::_set_direction(Vector2 direction)
{
	if (was_setted)
		return;

	is_attacking = true;
	_get_enemy()->call("_change_animation", "attack_start", 1.5f);

	cur_pos -= dir;

	was_setted = true;
	old_pos = _get_enemy()->get_global_position();
	_set_distance(_find_max_distance(direction));
	_set_speed(300);

	goal = cur_pos * 32 + CurrentRoom::get_singleton()->_get_current_room()
		->get_global_position() - Vector2(896, 544) / 2 + Vector2(16, 16);
	_set_distance(goal.distance_to(_get_enemy()->get_global_position()));

	if (sprite != nullptr)
	{
		if (goal.x >= cur_pos.x)
			sprite->set_flip_h(false);
		if (goal.x < cur_pos.x)
			sprite->set_flip_h(true);
	}
}

float godot::SillyBoyAI::_find_max_distance(Vector2 dir)
{
	float distance = 0;

	auto cur_room = CurrentRoom::get_singleton();

	while (cur_room->_get_current_room()->call("_is_empty_pos", cur_pos.y, cur_pos.x))
	{
		cur_pos += dir;
		distance += 32;
	}

	distance -= 32;
	cur_pos -= dir;

	return distance;
}

Vector2 godot::SillyBoyAI::_get_goal()
{
	return old_position;
}

void godot::SillyBoyAI::_set_goal(Vector2 goal)
{
	_set_distance(goal.distance_to(_get_enemy()->get_global_position()));

	this->goal = goal;

	cur_pos = (goal - CurrentRoom::get_singleton()->_get_current_room()->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;

	old_pos = _get_enemy()->get_global_position();
	old_position = old_pos;
}

godot::SillyBoyAI::SillyBoyAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	dir = Vector2::ZERO;

	can_move = true;
	_set_speed(200);
	old_position = _get_enemy()->get_global_position();
	_set_distance(32);
	_change_start_parameters();
	sprite = _get_enemy()->call("_get_animated_sprite");
}

godot::SillyBoyAI::~SillyBoyAI()
{
	directions.clear();
}

void godot::SillyBoyAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::SillyBoyAI::change_direction()
{
	reset_directions();

	auto cur_room = CurrentRoom::get_singleton()->_get_current_room();

	if ((int)cur_room->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::LEFT).x) == 0)
		directions.push_back(Vector2::LEFT);

	if ((int)cur_room->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::RIGHT).x) == 0)
		directions.push_back(Vector2::RIGHT);

	if ((int)cur_room->call("_get_cell_value", (cur_pos + Vector2::DOWN).y, cur_pos.x) == 0)
		directions.push_back(Vector2::DOWN);

	if ((int)cur_room->call("_get_cell_value", (cur_pos + Vector2::UP).y, cur_pos.x) == 0)
		directions.push_back(Vector2::UP);

	_fight(_get_player1(), _get_player2());

	_change_dir_after_time();
}

void godot::SillyBoyAI::_change_dir_after_time()
{
	if (sprite != nullptr)
	{
		if (is_attacking)
		{
			is_attacking = false;
			_get_enemy()->call("_change_animation", "attack_end", 2);
		}
		else
		{
			_get_enemy()->call("_change_animation", "idle", 1);
		}
	}

	if (directions.size() == 0)
	{
		goal = _get_enemy()->get_global_position();

		dir = Vector2::ZERO;
		return;
	}

	Ref<RandomNumberGenerator> rand = RandomNumberGenerator::_new();
	rand->randomize();

	dir = directions[rand->randi_range(0, directions.size() - 1)];
	goal = _get_enemy()->get_global_position() + dir * _get_distance();

	cur_pos += dir;

	if (sprite != nullptr)
	{
		if (dir == Vector2::RIGHT)
			sprite->set_flip_h(false);
		if (dir == Vector2::LEFT)
			sprite->set_flip_h(true);
	}
}

void godot::SillyBoyAI::_fight(Node2D* player1, Node2D* player2)
{
	can_move = false;
	if (!was_setted)
	{
		if (is_player1_onArea && player1 != nullptr)
			player1->call("_take_damage", damage, false);

		if (is_player2_onArea && player2 != nullptr)
			player2->call("_take_damage", damage, false);
	}

	was_setted = false;

	_get_enemy()->call("_start_timer");
}

void godot::SillyBoyAI::_process(float delta)
{
	if (!can_move)
		return;

	if (sprite != nullptr)
	{
		if (sprite->get_animation() == "attack_start"
			&& sprite->get_frame() == sprite->get_sprite_frames()->get_frame_count("attack_start") - 1
			|| is_attacking)
			sprite->play("attack_cycle");
	}


	_get_enemy()->set_global_position(_get_enemy()->get_global_position().move_toward(goal, delta * _get_speed()));

	if (sprite != nullptr)
	{
		if (!is_attacking && sprite->get_animation() != "damaged")
			_get_enemy()->call("_change_animation", "run", 2);
	}

	float distance = 32 > _get_distance() ? _get_distance() : 32;

	if (abs(old_position.distance_to(_get_enemy()->get_global_position()) - distance) <= 8)
	{
		auto cur_room_pos = CurrentRoom::get_singleton()->_get_current_room()->get_global_position();
		Vector2 cur_pos_tmp = (_get_enemy()->get_global_position() - cur_room_pos + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
		cur_pos_tmp = Vector2((int)cur_pos_tmp.x, (int)cur_pos_tmp.y);
		old_position = cur_pos_tmp * 32 + cur_room_pos - Vector2(896, 544) / 2 + Vector2(16, 16);
	}

	if (abs(old_pos.distance_to(_get_enemy()->get_global_position()) - _get_distance()) <= 1)
	{
		auto cur_room_pos = CurrentRoom::get_singleton()->_get_current_room()->get_global_position();
		was_setted = false;
		_set_speed(200);
		change_direction();
		old_pos = _get_enemy()->get_global_position();
		Vector2 cur_pos_tmp = (_get_enemy()->get_global_position() - cur_room_pos + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
		cur_pos_tmp = Vector2((int)cur_pos_tmp.x, (int)cur_pos_tmp.y);
		old_position = cur_pos_tmp * 32 + cur_room_pos - Vector2(896, 544) / 2 + Vector2(16, 16);
		return;
	}
}