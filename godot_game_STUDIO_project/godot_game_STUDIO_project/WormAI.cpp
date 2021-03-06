#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::WormAI::WormAI(Ref<PackedScene>& bullet, Node2D* node) : EnemyData(node)
{
	can_move = true;
	shooted = false;
	is_hided = false;
	prepare_to_shoot = true;
	auto bullet_container = node->get_parent()->get_node("BulletContainer");

	bullet_pull = new BulletPull(max_bullet_count, bullet, bullet_container);

	Array arr = CurrentRoom::get_singleton()->_get_current_room()->call("_get_enemy_spawn_positions");
	free_cells = arr[0];

	shoot_point = cast_to<Node2D>(node->get_node("ShootPoint"));
}

godot::WormAI::~WormAI()
{
	delete bullet_pull;
}

void godot::WormAI::change_can_fight(bool value)
{
	can_move = value;
	if (value)
	{
		if (finished_hide_anim)
		{
			//	after hide
			finished_hide_anim = false;
			_get_enemy()->call("_start_fixed_timer", .5f);
			_get_enemy()->set_visible(false);
			return;
		}

		if (is_hided && !prepare_to_shoot && !shooted)
		{
			//	shows in other place
			_on_show();
			return;
		}

		if (shooted && !is_hided && !prepare_to_shoot)
		{
			//	hide
			_on_hide();
			return;
		}
	}
}

void godot::WormAI::_fight(Node2D* player1, Node2D* player2)
{
	change_can_fight(false);
	_get_enemy()->call("_start_fixed_timer", 1.5f);
	_set_target();

	if (target == Vector2::ZERO)
		return;

	_get_enemy()->call("_change_animation", "attack", 1.5f);

	shooted = true;
	prepare_to_shoot = false;

	Vector2 bullet_dir = target;
	Vector2 bullet_position = shoot_point->get_global_position();

	Node2D* bullet = bullet_pull->_get_bullet();

	bullet->set_global_position(bullet_position);
	bullet->set_visible(true);
	bullet->call("_set_dir", (bullet_dir - bullet->get_global_position()).normalized());
}

void godot::WormAI::_process(float delta)
{
	if (can_move && !is_hided && prepare_to_shoot && !shooted)
		_fight();
}

void godot::WormAI::_add_bullet(Node* node)
{
	bullet_pull->_add_bullet(node->cast_to<Node2D>(node));
}

void godot::WormAI::_remove_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_delete_player1();

	if (player->is_in_group("player2"))
		_delete_player2();
}

void godot::WormAI::_set_target()
{
	if (MenuButtons::game_mode == COOP)
	{
		Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
		rng->randomize();
		if (rng->randi_range(1, 2) == 1)
		{
			if (_get_player1() != nullptr)
				target = _get_player1()->get_global_position();
			else if (_get_player2() != nullptr)
				target = _get_player2()->get_global_position();
			else
				target = Vector2::ZERO;
		}
		else
		{
			if (_get_player2() != nullptr)
				target = _get_player2()->get_global_position();
			else if (_get_player1() != nullptr)
				target = _get_player1()->get_global_position();
			else
				target = Vector2::ZERO;
		}
	}
	else
	{
		if (MenuButtons::game_mode == SHOOTER)
			target = _get_player1()->get_global_position();
		else if (MenuButtons::game_mode == MELEE)
			target = _get_player2()->get_global_position();
	}
}

void godot::WormAI::_set_next_pos()
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	Vector2 new_pos = free_cells[rng->randi_range(0, free_cells.size() - 1)];
	_get_enemy()->set_global_position(new_pos);
}

void godot::WormAI::_disable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, false);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, false);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, false);
}

void godot::WormAI::_on_hide()
{
	_disable_collisions();
	_get_enemy()->call("_change_animation", "hide", 1.5f);
	prepare_to_shoot = false;
	is_hided = true;
	shooted = false;
	change_can_fight(false);
	finished_hide_anim = true;
	_get_enemy()->call("_start_fixed_timer", .96f);
}

void godot::WormAI::_on_show()
{
	_set_next_pos();
	_get_enemy()->call("_change_animation", "show", 2.f);
	_get_enemy()->set_visible(true);
	prepare_to_shoot = true;
	is_hided = false;
	change_can_fight(false);
	_get_enemy()->call("_start_fixed_timer", 1.5f);
	_enable_collisions();
}

void godot::WormAI::_enable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, true);
}