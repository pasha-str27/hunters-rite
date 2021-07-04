#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerMelee::PlayerMelee(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
	_change_can_fight(true);
	current_enemy = nullptr;
	sprite = cast_to<AnimatedSprite>(obj->get_child(0));
	sprite->play("idle");

	vfx_sprite = cast_to<AnimatedSprite>(obj->get_node("Area2D3")->get_child(1));

	animator = cast_to<AnimationPlayer>(_get_object()->get_node("AnimationPlayer"));
	_set_special_time(1.5);

	cast_to<KinematicBody2D>(obj)->set_collision_mask_bit(1, true);
	cast_to<KinematicBody2D>(obj)->set_collision_layer_bit(0, true);
	cast_to<KinematicBody2D>(obj)->set_collision_layer_bit(15, true);
	cast_to<Area2D>(obj->get_node("Area2D"))->set_collision_mask_bit(0, true);
	cast_to<Area2D>(obj->get_node("Area2D"))->set_collision_layer_bit(0, true);
}

godot::PlayerMelee::~PlayerMelee()
{
	current_enemy = nullptr;

	sprite = nullptr;
	vfx_sprite = nullptr;

	animator = nullptr;
}

void godot::PlayerMelee::_move()
{
	PlayerData::_move();

	String animation_name = sprite->get_animation();
	if (sprite->get_sprite_frames()->get_animation_loop(animation_name) == false
		&& sprite->get_frame() == sprite->get_sprite_frames()->get_frame_count(animation_name) - 1)
	{
		sprite->set_offset(Vector2::ZERO);
		sprite->play("idle");
	}

	if (PlayerData::_get_dir() == Vector2::ZERO && animation_name != "revive"
		&& animation_name != "damaged" && animation_name != "attack")
		sprite->play("idle");

	if (PlayerData::_get_dir() != Vector2::ZERO && sprite->get_animation() == "idle")
		sprite->play("run");

	if (sprite->is_flipped_h() && sprite->get_animation() == "attack")
		sprite->set_offset(Vector2(-26, -4));
	else
		if (!sprite->is_flipped_h() && sprite->get_animation() == "attack")
			sprite->set_offset(Vector2(26, -4));
}

void godot::PlayerMelee::_process_input()
{
	Vector2 dir = Vector2(0, 0);

	//dash
	if (input_controller->is_action_just_pressed(special))
		_get_object()->call("_start_special_timer");

	//move up
	if (input_controller->is_action_pressed(move_up))
		dir.y -= _get_speed();

	//move down
	if (input_controller->is_action_pressed(move_down))
		dir.y += _get_speed();

	//move left
	if (input_controller->is_action_pressed(move_left))
	{
		sprite->set_flip_h(true);
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed(move_right))
	{
		sprite->set_flip_h(false);
		dir.x += _get_speed();
	}

	//fight	up
	if (input_controller->is_action_pressed(fight_up))
	{
		if (!is_attacking)
		{
			cast_to<Node2D>(_get_object()->get_node("Area2D3"))->set_rotation_degrees(270);
		}
		if (_can_fight())
		{
			animator->play("attack");
			is_attacking = true;
		}

	}

	//fight	down
	if (input_controller->is_action_pressed(fight_down))
	{
		if (!is_attacking)
		{
			cast_to<Node2D>(_get_object()->get_node("Area2D3"))->set_rotation_degrees(90);
		}
		if (_can_fight())
		{
			animator->play("attack");
			is_attacking = true;
		}
	}

	//fight	left
	if (input_controller->is_action_pressed(fight_left))
	{
		if (!is_attacking)
		{
			cast_to<Node2D>(_get_object()->get_node("Area2D3"))->set_rotation_degrees(180);
		}
		sprite->set_flip_h(true);
		if (_can_fight())
		{
			animator->play("attack");
			is_attacking = true;
		}
	}

	//fight	right
	if (input_controller->is_action_pressed(fight_right))
	{
		if (!is_attacking)
		{
			cast_to<Node2D>(_get_object()->get_node("Area2D3"))->set_rotation_degrees(0);
		}
		sprite->set_flip_h(false);
		if (_can_fight())
		{
			animator->play("attack");
			is_attacking = true;
		}
	}

	PlayerData::_set_dir(dir);
}

void godot::PlayerMelee::_fight(Node* node)
{
	if (!_can_fight())
		return;

	Ref<PackedScene> prefab = nullptr;
	prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/SoundsEffects/Effects/Player2Fight.tscn");
	_get_object()->add_child(prefab->instance());

	_change_can_fight(false);

	if (current_enemy)
	{
		Array args = {};
		args.push_back(_get_damage());
		args.push_back(2);
		current_enemy->call("_take_damage", args);
	}

	_get_object()->call("_start_timer");
}

void godot::PlayerMelee::_set_enemy(Node* enemy)
{
	current_enemy = enemy;
}

void godot::PlayerMelee::_take_damage(float damage, bool is_spike)
{
	if (_get_HP() <= 0)
		return;

	sprite->play("damaged");

	PlayerData::_take_damage(damage, is_spike);

	if (_get_HP() <= 0)
	{
		sprite->play("death");
		Enemies::get_singleton()->_remove_player2();
		_get_object()->call("_die");
	}
}

void godot::PlayerMelee::_set_HP(float value)
{
	PlayerData::_set_HP(value);

	if (_get_HP() <= 0)
	{
		Enemies::get_singleton()->_remove_player2();
		PlayersContainer::_get_instance()->_set_player2(nullptr);

		Godot::print(String::num(_was_revived()));

		if (_was_revived())
		{
			_get_object()->queue_free();
			return;
		}

		_get_object()->call("_die");
	}
}

void godot::PlayerMelee::_update_health_bar()
{
	auto health_bar = _get_health_bar();

	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerMelee::_get_health_bar()
{
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P2HealthBarWrapper/ProgressBar"));
}

void godot::PlayerMelee::_stop_animations()
{
	sprite->play("idle");
	sprite->set_offset(Vector2::ZERO);
	_set_dir(Vector2::ZERO);
	vfx_sprite->stop();
	vfx_sprite->set_frame(0);
}

void godot::PlayerMelee::_stop_special()
{
	_set_safe_mode(false);
	cast_to<Area2D>(_get_object()->get_node("Shield"))->set_collision_layer_bit(0, false);
	cast_to<Area2D>(_get_object()->get_node("Shield"))->set_collision_mask_bit(0, false);
	cast_to<AnimationPlayer>(_get_object()->get_node("Shield")->find_node("AnimationPlayer"))->play("shield_end");
}

void godot::PlayerMelee::_start_special()
{
	_set_safe_mode(true);
	cast_to<AnimationPlayer>(_get_object()->get_node("Shield")->find_node("AnimationPlayer"))->play("shield_start");

	cast_to<Area2D>(_get_object()->get_node("Shield"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(_get_object()->get_node("Shield"))->set_collision_mask_bit(0, true);
}

void godot::PlayerMelee::_set_is_attacking(bool value)
{
	is_attacking = value;
}
