#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::SpiderAI::SpiderAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
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

	old_pos = _get_enemy()->get_global_position();

	change_direction();
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

void godot::SpiderAI::reset_directions()
{
	directions.clear();
}

void godot::SpiderAI::change_direction()
{
	reset_directions();

	for (int i = 2; i < 6; ++i)
		if (!_get_enemy()->get_child(i)->call("_get_on_body"))
			directions.push_back(i - 1);

	_change_dir_after_time();
}

void godot::SpiderAI::_remove_side(int dir)
{
	directions.push_back(dir);
}

void godot::SpiderAI::_change_dir_after_time()
{
	if (directions.size() == 0)
	{
		dir = Vector2::ZERO;
		return;
	}	

	RandomNumberGenerator* rand = RandomNumberGenerator::_new();
	rand->randomize();

	is_cheking = false;

	switch (directions[rand->randi_range(0, directions.size() - 1)])
	{
	case 1:
		dir = Vector2(0, -0.5);
		break;
	case 2:
		cast_to<AnimatedSprite>(_get_enemy()->get_child(1)->get_child(0))->set_flip_h(true);
		dir = Vector2(-0.5, 0);
		break;
	case 3:
		cast_to<AnimatedSprite>(_get_enemy()->get_child(1)->get_child(0))->set_flip_h(false);
		dir = Vector2(0.5, 0);
		break;
	case 4:
		dir = Vector2(0, 0.5);
		break;
	default:
		break;
	}
}

void godot::SpiderAI::_fight(Node2D* player1, Node2D* player2)
{
	_get_enemy()->call("_change_animation", "idle", 1);

	can_move = false;
	_get_enemy()->call("_start_timer");

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();

	rng->randomize();

	Vector2 bullet_dir;

	if (player1 != nullptr && player2 != nullptr)
	{
		if (rng->randi_range(0, 2))
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

void godot::SpiderAI::_process(float delta)
{
	if (!can_move)
		return;

	_get_enemy()->set_global_position(_get_enemy()->get_global_position() + dir * delta * 235);

	if (is_cheking)
		return;

	if ((abs(old_pos.distance_to(_get_enemy()->get_global_position()) - 32) <= 3
		&& (dir == Vector2(0.5, 0) || dir == Vector2(-0.5, 0) || dir == Vector2(0, 0.5) || dir == Vector2(0, -0.5))
		|| (abs(old_pos.distance_to(_get_enemy()->get_global_position()) - sqrt(32 * 32 + 32 * 32)) <= 4.5
			&& (dir == Vector2(0.5, 0.5) || dir == Vector2(-0.5, 0.5) || dir == Vector2(0.5, -0.5) || dir == Vector2(-0.5, -0.5)))))
	{
		is_cheking = true;
		_fight(_get_player1(), _get_player2());
		change_direction();
		old_pos = _get_enemy()->get_global_position();
		return;
	}
}
