#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::WormAI::WormAI(Ref<PackedScene>& bullet, Node2D* node) :EnemyData(node)
{
	can_move = true;
	shooted = false;
	is_hided = false;
	prepare_to_shoot = true;
	auto bullet_container = node->get_parent()->get_node("BulletContainer");
	for (int i = 0; i < max_bullet_count; ++i)
	{
		Node2D* bullet_node = cast_to<Node2D>(bullet->instance());
		bullet_container->add_child(bullet_node);
		available_bullets.push_back(bullet_node);
	}
	ground_front = cast_to<AnimatedSprite>(_get_enemy()->find_node("GroundFront"));
	ground_back = cast_to<AnimatedSprite>(_get_enemy()->find_node("GroundBack"));
	Array arr = CameraController::current_room->call("_get_enemy_spawn_positions");
	free_cells = arr[0];
}

godot::WormAI::~WormAI()
{
	available_bullets.clear();
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
			ground_back->set_visible(true);
			return;
		}

		if (is_hided && !prepare_to_shoot && !shooted)
		{
			//	shows in other place
			_set_next_pos();
			_enable_collisions();
			_get_enemy()->set_visible(true);
			prepare_to_shoot = true;
			is_hided = false;
			ground_front->set_visible(false);
			ground_back->play("action");
			change_can_fight(false);
			_get_enemy()->call("_start_fixed_timer", 1.5f);
			_get_enemy()->call("_change_animation", "show", 1);
			return;
		}

		if (shooted && !is_hided && !prepare_to_shoot)
		{
			//	hide
			_disable_collisions();
			prepare_to_shoot = false;
			is_hided = true;
			shooted = false;
			change_can_fight(false);
			ground_front->set_visible(true);
			ground_back->set_visible(false);
			ground_front->play("action");
			finished_hide_anim = true;
			_get_enemy()->call("_start_fixed_timer", .4f);
			_get_enemy()->call("_change_animation", "hide", 1);
			return;
		}
	}
	
}

void godot::WormAI::_fight(Node2D* player1, Node2D* player2)
{
	change_can_fight(false);
	_get_enemy()->call("_start_fixed_timer", 1);
	_set_target();

	if (target == Vector2::ZERO)
		return;

	_get_enemy()->call("_change_animation", "attack", 1.5f);

	shooted = true;
	prepare_to_shoot = false;

	Vector2 bullet_dir = target;
	Vector2 bullet_position = cast_to<Node2D>(_get_enemy()->get_node("Area2D")->get_child(0))->get_global_position();

	if (available_bullets.size() > 0)
	{
		available_bullets[available_bullets.size() - 1]->set_global_position(bullet_position);

		available_bullets[available_bullets.size() - 1]->set_visible(true);

		available_bullets[available_bullets.size() - 1]->call("_set_dir",
			(bullet_dir - available_bullets[available_bullets.size() - 1]->get_global_position()).normalized());

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

void godot::WormAI::_process(float delta)
{
	String animation_name = ground_back->get_animation();

	if (ground_back->get_sprite_frames()->get_animation_loop(animation_name) == false && ground_back->get_frame() == ground_back->get_sprite_frames()->get_frame_count(animation_name) - 1)
		ground_back->play("idle");
	
	animation_name = ground_front->get_animation();

	if (ground_front->get_sprite_frames()->get_animation_loop(animation_name) == false && ground_front->get_frame() == ground_front->get_sprite_frames()->get_frame_count(animation_name) - 1)
		ground_front->play("idle");

	if (can_move && !is_hided && prepare_to_shoot && !shooted)
		_fight();
}

void godot::WormAI::_set_speed(float value)
{
}

void godot::WormAI::_add_bullet(Node* node)
{
	available_bullets.push_back(cast_to<Node2D>(node));
}

void godot::WormAI::_set_player(Node2D* player)
{

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

void godot::WormAI::_enable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, true);
}