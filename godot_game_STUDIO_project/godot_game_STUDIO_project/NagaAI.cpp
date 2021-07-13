#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::NagaAI::NagaAI(Ref<PackedScene>& bullet, Node2D* node) : EnemyData(node)
{
	can_move = true;
	speed = 80;
	damage = 75;

	poison = bullet;

	sprite = node->call("_get_animated_sprite");
	vampirism_particles = cast_to<Particles2D>(node->get_node("Vampirism"));

	timing_to_attack = .5f;
	teleport_speed = 1;
	attack_timing = 1;
	hide_time = 1;

	target_id = 0;
}

godot::NagaAI::~NagaAI()
{
	sprite = nullptr;
}

void godot::NagaAI::_process(float delta)
{
	if (can_move)
	{
		_follow_target(delta);
		if (can_attack && _is_player_near())
			_fight(_get_player1(), _get_player2());
	}
}

void godot::NagaAI::change_can_fight(bool value)
{
	can_move = value;

	if (!can_attack && !is_angry && !is_disappearing && _get_enemy()->is_visible() && is_teleported)
	{
		can_attack = true;
		is_teleported = false;
		return;
	}

	if (!can_attack && !is_angry && !is_disappearing && _get_enemy()->is_visible())
	{
		can_attack = true;
		return;
	}


	if (is_disappearing)
	{
		_disable_collisions();
		_get_enemy()->call("_change_animation", "disappear", teleport_speed);
		is_disappearing = false;
		can_move = false;
		_get_enemy()->call("_start_fixed_timer", .9f / teleport_speed);
		return;
	}

	if (is_angry && !is_disappearing && _get_enemy()->is_visible())
	{
		_get_enemy()->set_visible(false);
		can_move = false;
		_get_enemy()->call("_start_fixed_timer", hide_time);
		return;
	}

	if (is_angry)
	{
		_teleport_to_target();
		_get_enemy()->set_visible(true);
		_get_enemy()->call("_change_animation", "appear", teleport_speed);
		can_move = false;
		is_angry = false;
		_get_enemy()->call("_start_fixed_timer", timing_to_attack);
		_enable_collisions();
	}
}

void godot::NagaAI::_fight(Node2D* player1, Node2D* player2)
{
	if (!can_attack)
		return;

	can_move = false;

	if (is_player1_onArea && player1 != nullptr)
	{
		player1->call("_take_damage", damage, false);
		_get_enemy()->call("_change_animation", "attack", 1.5f);
		_make_vampirism();
	}

	if (is_player2_onArea && player2 != nullptr)
	{
		_get_enemy()->call("_change_animation", "attack", 1.5f);
		player2->call("_take_damage", damage, false);
		_make_vampirism();
	}

	_get_enemy()->call("_start_fixed_timer", attack_timing);
	can_attack = false;
	_check_target();
}

void godot::NagaAI::_remove_player(Node2D* player)
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

void godot::NagaAI::_set_target()
{

	Node2D* player1 = PlayersContainer::_get_instance()->_get_player1();
	Node2D* player2 = PlayersContainer::_get_instance()->_get_player2();

	if (MenuButtons::game_mode == COOP)
	{
		Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
		rng->randomize();
		if (rng->randi_range(1, 2) == 1)
		{
			if (_get_player1() != nullptr && player1 != nullptr)
			{
				target = _get_player1();
				target_id = 1;
			}
			else if (_get_player2() != nullptr && player2 != nullptr)
			{
				target = _get_player2();
				target_id = 2;
			}
			else
			{
				target = nullptr;
				target_id = 0;
			}
		}
		else
		{
			if (_get_player2() != nullptr && player2 != nullptr)
			{
				target = _get_player2();
				target_id = 2;

			}
			else if (_get_player1() != nullptr && player1 != nullptr)
			{
				target = _get_player1();
				target_id = 1;

			}
			else
			{
				target = nullptr;
				target_id = 0;
			}
		}
	}
	else
	{
		if (MenuButtons::game_mode == SHOOTER && player1 != nullptr)
		{
			target = _get_player1();
			target_id = 1;

		}
		else if (MenuButtons::game_mode == MELEE && player2 != nullptr)
		{
			target = _get_player2();
			target_id = 2;

		}
	}
}

void godot::NagaAI::_set_next_pos()
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();
	_set_target();
	_get_enemy()->set_global_position(target->get_global_position() + Vector2(rng->randi_range(-32, 32), rng->randi_range(-32, 32)));
	is_teleported = true;
	can_attack = false;
}

void godot::NagaAI::_disable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, false);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, false);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, false);
}

void godot::NagaAI::_follow_target(float delta)
{
	if(target == nullptr)
		_set_target();

	_get_enemy()->call("_change_animation", "run", 1);
	_get_enemy()->set_global_position(_get_enemy()->get_global_position().move_toward(target->get_global_position(), delta * speed));

	if (sprite != nullptr)
	{
		if (target->get_global_position().x >= _get_enemy()->get_global_position().x)
		{
			sprite->set_offset(Vector2(0, 0));
			sprite->set_flip_h(false);
		}
		else
		{
			sprite->set_offset(Vector2(-25, 0));
			sprite->set_flip_h(true);
		}
	}
}

void godot::NagaAI::_take_damage(float damage)
{
	_spawn_egg(_get_enemy()->get_global_position());
	can_move = false;
	is_angry = true;
	is_disappearing = true;
	_get_enemy()->call("_start_fixed_timer", .3f);

	if ((float)_get_enemy()->call("_get_HP_percent") <= 75)
		_decrease_cooldowns();
}

void godot::NagaAI::_teleport_to_target()
{
	_set_next_pos();
}

bool godot::NagaAI::_is_player_near()
{ 
	return is_player1_onArea || is_player2_onArea;
}

void godot::NagaAI::_make_vampirism()
{
	_get_enemy()->call("_add_to_HP", damage);
	vampirism_particles->restart();
	if ((float)_get_enemy()->call("_get_HP_percent") > 75)
		_increase_cooldowns();
}

void godot::NagaAI::_check_target()
{
	if (target_id == 1 && PlayersContainer::_get_instance()->_get_player1() == nullptr 
		|| target_id == 2 && PlayersContainer::_get_instance()->_get_player2() == nullptr)
		_set_target();
}

void godot::NagaAI::_spawn_egg(Vector2 pos)
{
	auto egg = cast_to<Node2D>(poison->instance());
	_get_enemy()->get_node("/root/Node2D/Node")->call_deferred("add_child", egg);
	egg->set_global_position(pos + Vector2(0, 30));
}

void godot::NagaAI::_decrease_cooldowns()
{
	timing_to_attack = .35f;
	teleport_speed = 1.5f;
	attack_timing = .5f;
	hide_time = .5f;
	speed = 120;
}

void godot::NagaAI::_increase_cooldowns()
{
	timing_to_attack = .5f;
	teleport_speed = 1;
	attack_timing = 1;
	hide_time = 1;
	speed = 80;
}

void godot::NagaAI::_enable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, true);
}

void godot::NagaAI::_set_is_player1_onArea(bool value)
{
	is_player1_onArea = value;
}

void godot::NagaAI::_set_is_player2_onArea(bool value)
{
	is_player2_onArea = value;
}

void godot::NagaAI::_set_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_set_is_player1_onArea(true);

	if (player->is_in_group("player2"))
		_set_is_player2_onArea(true);

	_fight(_get_player1(), _get_player2());
}