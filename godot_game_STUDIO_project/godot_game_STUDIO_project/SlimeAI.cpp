#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

bool godot::SlimeAI::_is_player_near(Node2D* player)
{
	Vector2 player_pos_index = (player->get_global_position()
		- CameraController::current_room->get_global_position()
		+ Vector2(896, 544) / 2) / _get_distance();

	bool is_player_ghost = (bool)player->call("_is_ghost_mode");

	bool ghost_is_near = false;

	player_pos_index = Vector2((int)player_pos_index.y, (int)player_pos_index.x);

	Vector2 new_pos = Vector2((int)cur_pos.y, (int)(cur_pos + Vector2::LEFT).x);

	if (player_pos_index == new_pos && (bool)CameraController::current_room->call("_is_empty_pos", new_pos.x, new_pos.y))
	{
		if (!is_player_ghost)
		{
			directions.clear();
			directions.push_back(Vector2::LEFT);
			return true;
		}

		ghost_is_near = true;
		remove_vector_element(Vector2::LEFT);
	}

	new_pos = Vector2((int)cur_pos.y, (int)(cur_pos + Vector2::RIGHT).x);

	if (player_pos_index == new_pos && (bool)CameraController::current_room->call("_is_empty_pos", new_pos.x, new_pos.y))
	{
		if (!is_player_ghost)
		{
			directions.clear();
			directions.push_back(Vector2::RIGHT);
			return true;
		}

		ghost_is_near = true;
		remove_vector_element(Vector2::RIGHT);
	}

	new_pos = Vector2((int)(cur_pos + Vector2::DOWN).y, (int)cur_pos.x);

	if (player_pos_index == new_pos && (bool)CameraController::current_room->call("_is_empty_pos", new_pos.x, new_pos.y))
	{
		if (!is_player_ghost)
		{
			directions.clear();
			directions.push_back(Vector2::DOWN);
			return true;
		}

		ghost_is_near = true;
		remove_vector_element(Vector2::DOWN);
	}

	new_pos = Vector2((int)(cur_pos + Vector2::UP).y, (int)cur_pos.x);

	if (player_pos_index == new_pos && (bool)CameraController::current_room->call("_is_empty_pos", new_pos.x, new_pos.y))
	{
		if (!is_player_ghost)
		{
			directions.clear();
			directions.push_back(Vector2::UP);
			return true;
		}

		ghost_is_near = true;
		remove_vector_element(Vector2::UP);
	}

	if (ghost_is_near)
		return true;

	return false;
}

void godot::SlimeAI::_set_speed(float value)
{
	speed = value;
}

void godot::SlimeAI::_set_is_player1_onArea(bool value)
{
	is_player1_onArea = value;
	was_setted = true;
}

void godot::SlimeAI::_set_is_player2_onArea(bool value)
{
	is_player2_onArea = value;
	was_setted = true;
}

void godot::SlimeAI::_change_start_parameters()
{
	cur_pos = (_get_enemy()->get_global_position() - CameraController::current_room->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / _get_distance();

	old_pos = _get_enemy()->get_global_position();

	change_direction();
}

void godot::SlimeAI::_set_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_set_is_player1_onArea(true);

	if(player->is_in_group("player2"))
		_set_is_player2_onArea(true);
}

void godot::SlimeAI::_remove_player(Node2D* player)
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

godot::SlimeAI::SlimeAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	dir = Vector2::ZERO;

	can_move = true;
	is_cheking = false;
	speed = 400;
	_change_start_parameters();
}

godot::SlimeAI::~SlimeAI()
{
	directions.clear();
}

void godot::SlimeAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::SlimeAI::change_direction()
{
	reset_directions();

	if ((int)CameraController::current_room->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::LEFT).x) == 0)
		directions.push_back(Vector2::LEFT);

	if ((int)CameraController::current_room->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::RIGHT).x) == 0)
		directions.push_back(Vector2::RIGHT);

	if ((int)CameraController::current_room->call("_get_cell_value", (cur_pos + Vector2::DOWN).y, cur_pos.x) == 0)
		directions.push_back(Vector2::DOWN);

	if ((int)CameraController::current_room->call("_get_cell_value", (cur_pos + Vector2::UP).y, cur_pos.x) == 0)
		directions.push_back(Vector2::UP);

	_fight(_get_player1(), _get_player2());

	PlayersContainer* players = PlayersContainer::_get_instance();

	//перевірити
	if (players->_get_player1() == nullptr && players->_get_player1_regular() != nullptr
		&& (bool)players->_get_player1_regular()->call("_is_ghost_mode") 
		&& _is_player_near(players->_get_player1_regular()));

	if (players->_get_player2() == nullptr && players->_get_player2_regular() != nullptr
		&& (bool)players->_get_player2_regular()->call("_is_ghost_mode")
		&& _is_player_near(players->_get_player2_regular()));

	bool is_player_near = false;

	if (players->_players_count() > 0)
	{
		if (players->_get_player1() != nullptr
			&& players->_get_player2() != nullptr)
		{
			Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
			random->randomize();

			if (random->randi_range(0, 1))
			{
				is_player_near = _is_player_near(players->_get_player2());
				if(!is_player_near)
					is_player_near = _is_player_near(players->_get_player1());
			}
			else
			{
				is_player_near = _is_player_near(players->_get_player1());
				if (!is_player_near)
					is_player_near = _is_player_near(players->_get_player2());
			}
		}
		else
		{
			if (players->_get_player1() == nullptr)
				is_player_near = _is_player_near(players->_get_player2());
			else
				is_player_near = _is_player_near(players->_get_player1());
		}
	}

	_change_dir_after_time();
}

void godot::SlimeAI::_change_dir_after_time()
{
	if (directions.size() == 0)
	{
		goal = _get_enemy()->get_global_position();

		dir = Vector2::ZERO;
		return;
	}	

	Ref<RandomNumberGenerator> rand = RandomNumberGenerator::_new();
	rand->randomize();

	is_cheking = false;

	dir = directions[rand->randi_range(0, directions.size() - 1)];
	goal = _get_enemy()->get_global_position() + dir * _get_distance();

	cur_pos += dir;

	if (dir == Vector2::RIGHT)
		cast_to<AnimatedSprite>(_get_enemy()->find_node("AnimatedSprite"))->set_flip_h(true);
	if (dir == Vector2::LEFT)
		cast_to<AnimatedSprite>(_get_enemy()->find_node("AnimatedSprite"))->set_flip_h(false);
}

void godot::SlimeAI::_fight(Node2D* player1, Node2D* player2)
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

void godot::SlimeAI::_process(float delta)
{
	if (!can_move)
		return;

	_get_enemy()->set_global_position(_get_enemy()->get_global_position().move_toward(goal, delta*speed));

	if (is_cheking)
		return;

	if (abs(old_pos.distance_to(_get_enemy()->get_global_position()) - _get_distance()) <= 1)
	{
		is_cheking = true;
		change_direction();
		old_pos = _get_enemy()->get_global_position();
		return;
	}
}