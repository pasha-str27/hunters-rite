#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::SlimeBossAI::SlimeBossAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	can_move = true;
	_attack_state = new SlimeAttackSpawnState(this);

	auto bullet_container = node_tmp->get_parent()->get_node("BulletContainer");
	for (int i = 0; i < max_bullet_count; ++i)
	{
		Node2D* bullet_node = cast_to<Node2D>(bullet->instance());
		bullet_container->add_child(bullet_node);
		available_bullets.push_back(bullet_node);
	}
	jump_zone = cast_to<Node2D>(_get_enemy()->get_parent()->get_node("jump_zone"));
}

godot::SlimeBossAI::~SlimeBossAI()
{
	available_bullets.clear();
}

void godot::SlimeBossAI::_set_player(Node2D* player)
{
	target_player = player->get_global_position();
}

void godot::SlimeBossAI::_remove_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_delete_player1();

	if (player->is_in_group("player2"))
		_delete_player2();
}

void godot::SlimeBossAI::_change_state(ISlimeAttackState* state)
{
	_attack_state = state;
}

void godot::SlimeBossAI::change_can_fight(bool value, ISlimeAttackState* state)
{
	can_move = value;
	
	_attack_state = state;
}

void godot::SlimeBossAI::_wait(float time)
{
	_get_enemy()->call("_start_fixed_timer", time);
}

void godot::SlimeBossAI::_add_bullet(Node* node)
{
	available_bullets.push_back(cast_to<Node2D>(node));
}

void godot::SlimeBossAI::_shoot()
{
	change_can_fight(false);

	if (target_player == Vector2::ZERO)
		return;

	Vector2 bullet_dir = target_player;
	float angle = M_PI / 9;

	if (available_bullets.size() > 0)
	{
		for (int i = 0; i < 3; i++)
		{
			available_bullets[available_bullets.size() - 1]->set_global_position(_get_enemy()->get_global_position());

			available_bullets[available_bullets.size() - 1]->set_visible(true);

			available_bullets[available_bullets.size() - 1]->call("_set_dir",
				(bullet_dir - available_bullets[available_bullets.size() - 1]->get_global_position()).normalized());

			bullet_dir = target_player;
			bullet_dir.x = bullet_dir.x * cos(angle / 3) - bullet_dir.y * sin(angle / 3);
			bullet_dir.y = bullet_dir.x * sin(angle / 3) + bullet_dir.y * cos(angle / 3);
			angle = -(M_PI / 9);

			if (available_bullets.size() == 1)
			{
				auto node = _get_enemy()->get_parent()->get_child(0);
				auto new_obj = available_bullets[0]->duplicate(8);
				node->add_child(new_obj);
				available_bullets.push_back(cast_to<Node2D>(new_obj));
			}

			available_bullets.pop_back();

		}		
	}
	_wait(1.5f);
}

void godot::SlimeBossAI::_spawn_enemy()
{
}

void godot::SlimeBossAI::_jump()
{
	is_jumping = true;
	jumping_up = true;
	goal = _get_enemy()->get_global_position() - Vector2(0, 720);
	cast_to<Node2D>(_get_enemy()->get_node("CollisionShape2D"))->hide();
}

void godot::SlimeBossAI::_jumping(float delta)
{
	_get_enemy()->set_global_position(_get_enemy()->get_global_position().move_toward(goal, delta * 1000));

	if (abs(goal.distance_to(_get_enemy()->get_global_position())) <= 1)
	{
		is_jumping = false;
		if (jumping_up)
		{
			_set_target();
			_get_enemy()->set_global_position(Vector2(target_player.x, _get_enemy()->get_global_position().y));
			_show_jump_zone();
		}
		else
		{
			cast_to<Node2D>(_get_enemy()->get_node("CollisionShape2D"))->show();
			jump_zone->set_visible(false);
			_wait(.5f);
		}
	}
}

void godot::SlimeBossAI::_show_jump_zone()
{
	jump_zone->set_global_position(target_player);
	cast_to<AnimationPlayer>(jump_zone->get_node("Animator"))->play("grow");
	_start_falling();
}

void godot::SlimeBossAI::_start_falling()
{
	goal = target_player;
	is_jumping = true;
	jumping_up = false;
}

void godot::SlimeBossAI::_set_target()
{
	if (MenuButtons::player_name == 0)
	{
		Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
		rng->randomize();
		if (rng->randi_range(1, 2) == 1)
		{
			if (_get_player1() != nullptr)
				target_player = _get_player1()->get_global_position();
			else if (_get_player2() != nullptr)
				target_player = _get_player2()->get_global_position();
			else
				target_player = Vector2::ZERO;
		}
		else
		{
			if (_get_player2() != nullptr)
				target_player = _get_player2()->get_global_position();
			else if (_get_player1() != nullptr)
				target_player = _get_player1()->get_global_position();
			else
				target_player = Vector2::ZERO;
		}
	}
	else
	{
		if (MenuButtons::player_name == 1)
			target_player = _get_player1()->get_global_position();
		else if (MenuButtons::player_name == 2)
			target_player = _get_player2()->get_global_position();
	}
}

void godot::SlimeBossAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::SlimeBossAI::_fight(Node2D* player1, Node2D* player2)
{
	if (can_move)
	{
		can_move = false;
		is_attacking = true;
		_attack_state->_fight();
	}

}

void godot::SlimeBossAI::_process(float delta)
{
	if (is_jumping)
		_jumping(delta);

	_fight();
}

void godot::SlimeBossAI::_set_speed(float value)
{
	speed = value;
}
