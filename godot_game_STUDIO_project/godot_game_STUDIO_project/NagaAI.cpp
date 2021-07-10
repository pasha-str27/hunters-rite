#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::NagaAI::NagaAI(Ref<PackedScene>& bullet, Node2D* node) : EnemyData(node)
{
	can_move = true;
	speed = 100;

	sprite = node->call("_get_animated_sprite");
	vampirism_particles = cast_to<Particles2D>(node->get_node("Vampirism"));
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
		_get_enemy()->call("_change_animation", "disappear", 1);
		is_disappearing = false;
		can_move = false;
		_get_enemy()->call("_start_fixed_timer", .9f);
		return;
	}

	if (is_angry && !is_disappearing && _get_enemy()->is_visible())
	{
		_get_enemy()->set_visible(false);
		can_move = false;
		_get_enemy()->call("_start_fixed_timer", 1);
		return;
	}

	if (is_angry)
	{
		_teleport_to_target();
		_get_enemy()->set_visible(true);
		_get_enemy()->call("_change_animation", "appear", 1);
		can_move = false;
		is_angry = false;
		_get_enemy()->call("_start_fixed_timer", .5f);
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

	_get_enemy()->call("_start_fixed_timer", 1.5f);
	can_attack = false;
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
	if (MenuButtons::game_mode == COOP)
	{
		Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
		rng->randomize();
		if (rng->randi_range(1, 2) == 1)
		{
			if (_get_player1() != nullptr)
				target = _get_player1();
			else if (_get_player2() != nullptr)
				target = _get_player2();
			else
				target = nullptr;
		}
		else
		{
			if (_get_player2() != nullptr)
				target = _get_player2();
			else if (_get_player1() != nullptr)
				target = _get_player1();
			else
				target = nullptr;
		}
	}
	else
	{
		if (MenuButtons::game_mode == SHOOTER)
			target = _get_player1();
		else if (MenuButtons::game_mode == MELEE)
			target = _get_player2();
	}
}

void godot::NagaAI::_set_next_pos()
{
	_set_target();
	_get_enemy()->set_global_position(target->get_global_position());
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
	can_move = false;
	is_angry = true;
	is_disappearing = true;
	_get_enemy()->call("_start_fixed_timer", .7f);
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