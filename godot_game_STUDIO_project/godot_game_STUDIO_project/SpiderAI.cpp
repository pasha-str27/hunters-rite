#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::SpiderAI::SpiderAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	dir = Vector2::ZERO;
	
	max_bullet_count = 5;
	can_move = true;
	is_cheking = false;
	speed = 400;

	auto node = _get_enemy()->get_parent()->get_child(0);

	for (int i = 0; i < max_bullet_count; ++i)
	{
		auto new_obj = bullet->instance();
		node->add_child(new_obj);
		bullets.push_back(cast_to<Node2D>(new_obj));
	}
}

godot::SpiderAI::~SpiderAI()
{
	bullets.clear();
	directions.clear();
}

void godot::SpiderAI::_add_bullet(Node* node)
{
	bullets.push_back(cast_to<Node2D>(node));
}

void godot::SpiderAI::change_can_fight(bool value)
{
	can_move = value;
	if(value)
		_get_enemy()->call("_change_animation", "run", 2);
}

bool godot::SpiderAI::_is_player_near(Node2D* player)
{
	Vector2 player_pos_index = (player->get_global_position()
		- CameraController::current_room->get_global_position()
		+ Vector2(896, 544) / 2) / _get_distance();

	bool is_player_ghost = (bool)player->call("_is_ghost_mode");

	bool ghost_is_near = false;

	player_pos_index = Vector2((int)player_pos_index.y, (int)player_pos_index.x);

	if (is_player_ghost)
	{
		if (player_pos_index == Vector2((int)cur_pos.y, (int)(cur_pos + Vector2::LEFT).x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::LEFT);
		}

		if (player_pos_index == Vector2((int)cur_pos.y, (int)(cur_pos + Vector2::RIGHT).x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::RIGHT);
		}

		if (player_pos_index == Vector2((int)(cur_pos + Vector2::DOWN).y, (int)cur_pos.x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::DOWN);
		}

		if (player_pos_index == Vector2((int)(cur_pos + Vector2::UP).y, (int)cur_pos.x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::UP);
		}
	}

	if (ghost_is_near)
		return true;

	return false;
}

void godot::SpiderAI::change_direction()
{
	reset_directions();

	if((int)CameraController::current_room->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::LEFT).x)==0)
		directions.push_back(Vector2::LEFT);

	if ((int)CameraController::current_room->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::RIGHT).x) == 0)
		directions.push_back(Vector2::RIGHT);

	if ((int)CameraController::current_room->call("_get_cell_value", (cur_pos + Vector2::DOWN).y, cur_pos.x) == 0)
		directions.push_back(Vector2::DOWN);

	if ((int)CameraController::current_room->call("_get_cell_value", (cur_pos + Vector2::UP).y, cur_pos.x) == 0)
		directions.push_back(Vector2::UP);

	PlayersContainer* players = PlayersContainer::_get_instance();

	if (players->_get_player1() == nullptr && players->_get_player1_regular() != nullptr
		&& (bool)players->_get_player1_regular()->call("_is_ghost_mode")
		&& _is_player_near(players->_get_player1_regular()));

	if (players->_get_player2() == nullptr && players->_get_player2_regular() != nullptr
		&& (bool)players->_get_player2_regular()->call("_is_ghost_mode")
		&& _is_player_near(players->_get_player2_regular()));

	_change_dir_after_time();
}

void godot::SpiderAI::_change_dir_after_time()
{
	if (directions.size() == 0)
	{
		dir = Vector2::ZERO;
		goal = _get_enemy()->get_global_position();
		return;
	}	

	Ref<RandomNumberGenerator> rand = RandomNumberGenerator::_new();
	rand->randomize();

	is_cheking = false;

	dir = directions[rand->randi_range(0, directions.size() - 1)];
	goal = _get_enemy()->get_global_position() + dir * _get_distance();
	cur_pos += dir;
}

void godot::SpiderAI::_fight(Node2D* player1, Node2D* player2)
{
	_get_enemy()->call("_change_animation", "idle", 1);

	can_move = false;
	_get_enemy()->call("_start_timer");

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();

	rng->randomize();

	Vector2 bullet_dir;

	if (player1 != nullptr && player2 != nullptr)
	{
		if (rng->randi_range(0, 1))
			bullet_dir = player2->get_global_position();
		else
			bullet_dir = player1->get_global_position();
	}
	else
	{
		if (player1 != nullptr && player2 == nullptr)
			bullet_dir = player1->get_global_position();
		else
		{
			if (player1 == nullptr && player2 != nullptr)
				bullet_dir = player2->get_global_position();
			else
				bullet_dir = Vector2(rng->randf_range(-1, 1), rng->randf_range(-1, 1));
		}
	}

	if (bullets.size() > 0)
	{
		bullets[bullets.size() - 1]->set_global_position(_get_enemy()->get_global_position());

		bullets[bullets.size() - 1]->set_visible(true);

		bullets[bullets.size() - 1]->call("_set_dir", (bullet_dir - bullets[bullets.size() - 1]->get_global_position()).normalized());

		if (bullets.size() == 1)
		{
			auto node = _get_enemy()->get_parent()->get_child(0);
			auto new_obj = bullets[0]->duplicate(8);
			node->add_child(new_obj);
			bullets.push_back(cast_to<Node2D>(new_obj));
		}

		bullets.pop_back();
	}
}

void godot::SpiderAI::_set_speed(float value)
{
	speed = value;
}

void godot::SpiderAI::_change_start_parameters()
{
	cur_pos = (_get_enemy()->get_global_position() - CameraController::current_room->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / _get_distance();
	old_pos = _get_enemy()->get_global_position();

	change_direction();
}

void godot::SpiderAI::_process(float delta)
{
	if (!can_move)
		return;

	_get_enemy()->set_global_position(_get_enemy()->get_global_position().move_toward(goal, delta * speed));
	if (is_cheking)
		return;

	if (abs(old_pos.distance_to(_get_enemy()->get_global_position()) - _get_distance()) <= 1)
	{
		is_cheking = true;
		_fight(_get_player1(), _get_player2());
		change_direction();
		old_pos = _get_enemy()->get_global_position();
		return;
	}
}
