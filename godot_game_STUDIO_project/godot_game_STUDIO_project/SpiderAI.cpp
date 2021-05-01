#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

godot::SpiderAI::SpiderAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2)
{
	max_bullet_count = 5;
	enemy = node_tmp;
	can_move = true;
	is_cheking = false;
	speed = 400;

	auto node = node_tmp->get_node("/root/Node2D/Node/BulletConteinerSpider");

	for (int i = 0; i < max_bullet_count; ++i)
	{
		auto new_obj = bullet->instance();
		node->add_child(new_obj);
		bullets.push_back(cast_to<Node2D>(new_obj));
	}

	change_direction();
}

void godot::SpiderAI::_add_bullet(Node* node)
{
	bullets.push_back(cast_to<Node2D>(node));
}

void godot::SpiderAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::SpiderAI::reset_directions()
{
	directions.clear();
}

void godot::SpiderAI::change_direction()
{
	reset_directions();
	for (int i = 2; i < 6; ++i)
	{
		if (!enemy->get_child(i)->call("_get_on_body"))
			directions.push_back(i - 1);
	}

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
		dir = Vector2(-0.5, 0);
		break;
	case 3:
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
	can_move = false;
	enemy->call("_start_timer");

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
				bullet_dir = Vector2(rng->randf_range(-100, 100), rng->randf_range(-100, 100));
		}
	}

	if (bullets.size() > 0)
	{
		bullets[bullets.size() - 1]->set_global_position(enemy->get_global_position());

		bullets[bullets.size() - 1]->set_visible(true);

		bullets[bullets.size() - 1]->call("_set_dir", (bullet_dir - bullets[bullets.size() - 1]->get_global_position()).normalized());

		if (bullets.size() == 1)
		{
			auto node = enemy->get_node("/root/Node2D/Node/BulletConteinerSpider");
			auto new_obj = bullets[0]->duplicate(8);
			node->add_child(new_obj);
			bullets.push_back(cast_to<Node2D>(new_obj));
		}

		bullets.pop_back();
	}
}

void godot::SpiderAI::_delete_player1(Node2D* player1, Node2D* player2)
{
}

void godot::SpiderAI::_delete_player2(Node2D* player1, Node2D* player2)
{
}

String godot::SpiderAI::_get_current_player()
{
	return String();
}

void godot::SpiderAI::_set_speed(float value)
{
	speed = value;
}

void godot::SpiderAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	if (!can_move)
		return;

	cast_to<KinematicBody2D>(enemy)->move_and_slide(dir * speed);

	if (is_cheking)
		return;

	if (enemy->get_global_position().x >= 0 && enemy->get_global_position().y >= 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16) <= 0.8
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32 - 16) <= 0.8 && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32 + 16));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}

	if (enemy->get_global_position().x < 0 && enemy->get_global_position().y < 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16) <= 0.8
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32 + 16) <= 0.8 && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32 - 16));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}
	
	if (enemy->get_global_position().x < 0 && enemy->get_global_position().y > 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16) <= 0.8
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32 - 16) <= 0.8 && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32 + 16));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}
	
	if (enemy->get_global_position().x > 0 && enemy->get_global_position().y < 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16) <= 0.8
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32 + 16) <= 0.8 && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32 - 16));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}
}
