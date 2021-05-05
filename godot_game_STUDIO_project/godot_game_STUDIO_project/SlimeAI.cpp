#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

Vector2 godot::SlimeAI::directions_swich(int value)
{
	float d = .5f;
	Vector2 direction;
	switch (value)
	{
	case 1:
		direction = Vector2(-d, -d);
		break;
	case 2:
		direction = Vector2(0, -d);
		break;
	case 3:
		direction = Vector2(d, -d);
		break;
	case 4:
		direction = Vector2(-d, 0);
		break;
	case 5:
		direction = Vector2(d, 0);
		break;
	case 6:
		direction = Vector2(-d, d);
		break;
	case 7:
		direction = Vector2(0, d);
		break;
	case 8:
		direction = Vector2(d, d);
		break;
	default:
		break;
	}

	return direction;
}

void godot::SlimeAI::_delete_player1(Node2D* player1, Node2D* player2)
{
}

void godot::SlimeAI::_delete_player2(Node2D* player1, Node2D* player2)
{
}

String godot::SlimeAI::_get_current_player()
{
	return String();
}

void godot::SlimeAI::_set_speed(float value)
{
	speed = value;
}

godot::SlimeAI::SlimeAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2)
{
	enemy = node_tmp;
	can_move = true;
	is_cheking = false;
	speed = 400;

	old_pos = enemy->get_global_position();

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
	for (int i = 2; i < 9; ++i)
	{
		if (enemy->get_child(i)->call("_get_current_node") != nullptr
			&& cast_to<Node2D>(enemy->get_child(i)->call("_get_current_node"))->is_in_group("player")
			&& (bool)cast_to<Node2D>(enemy->get_child(i)->call("_get_current_node"))->call("_is_alive"))
		{
			dir = directions_swich(i - 1);
			is_cheking = false;
			return;
		}
		if (!enemy->get_child(i)->call("_get_on_body"))
			directions.push_back(i - 1);
	}

	_change_dir_after_time();
	//enemy->call("_start_timer_for_dir_change");
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
	enemy->call("_start_timer");
}

void godot::SlimeAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	if (!can_move)
		return;

	Godot::print(String::num(old_pos.distance_to(enemy->get_global_position())));
	cast_to<KinematicBody2D>(enemy)->set_global_position(cast_to<KinematicBody2D>(enemy)->get_global_position() + dir * delta * 235);

	if (is_cheking)
		return;

	
	//cast_to<KinematicBody2D>(enemy)->move_and_slide(dir * speed);

	if ((abs(old_pos.distance_to(enemy->get_global_position())-32) <= 3
		&&(dir==Vector2(0.5,0)|| dir == Vector2(-0.5, 0)|| dir == Vector2(0, 0.5)|| dir == Vector2(0, -0.5))
			|| (abs(old_pos.distance_to(enemy->get_global_position()) - sqrt(32*32+32*32)) <= 4.5
			&& (dir == Vector2(0.5, 0.5) || dir == Vector2(-0.5, 0.5) || dir == Vector2(0.5, -0.5) || dir == Vector2(-0.5, -0.5)))))
	{
		/*if (enemy->get_global_position().x >= 0 && enemy->get_global_position().y >= 0)
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));
		
		if (enemy->get_global_position().x < 0 && enemy->get_global_position().y < 0)
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));

		if (enemy->get_global_position().x < 0 && enemy->get_global_position().y > 0)
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));

		if (enemy->get_global_position().x > 0 && enemy->get_global_position().y < 0)
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));*/

		is_cheking = true;
		_fight(player1, player2);
		change_direction();
		old_pos = enemy->get_global_position();
		return;
	}


	/*if (enemy->get_global_position().x >= 0 && enemy->get_global_position().y >= 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16) <= epsilone
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32) <= epsilone && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}

	if (enemy->get_global_position().x < 0 && enemy->get_global_position().y < 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16) <= epsilone
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32) <= epsilone && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}

	if (enemy->get_global_position().x < 0 && enemy->get_global_position().y > 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16) <= epsilone
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32) <= epsilone && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}

	if (enemy->get_global_position().x > 0 && enemy->get_global_position().y < 0)
	{
		if (abs(enemy->get_global_position().x - ((int)(round(enemy->get_global_position().x)) / 32) * 32 - 16) <= epsilone
			&& abs(enemy->get_global_position().y - ((int)(round(enemy->get_global_position().y)) / 32) * 32) <= epsilone && !is_cheking)
		{
			enemy->set_global_position(Vector2(((int)(round(enemy->get_global_position().x)) / 32) * 32 + 16, ((int)(round(enemy->get_global_position().y)) / 32) * 32));
			is_cheking = true;
			_fight(player1, player2);
			change_direction();
			return;
		}
	}*/
}

void godot::SlimeAI::_add_bullet(Node* node)
{
}
