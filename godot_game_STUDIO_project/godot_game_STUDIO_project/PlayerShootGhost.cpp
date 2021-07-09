#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerShootGhost::PlayerShootGhost(Node2D* object, Ref<PackedScene> bullet) : PlayerData(object)
{
	cast_to<KinematicBody2D>(object)->set_collision_mask_bit(1, false);
	cast_to<KinematicBody2D>(object)->set_collision_layer_bit(0, false);
	cast_to<KinematicBody2D>(object)->set_collision_layer_bit(15, false);
	cast_to<Area2D>(object->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<Area2D>(object->get_node("Area2D"))->set_collision_layer_bit(0, false);

	_change_can_fight(true);

	auto node = _get_object()->get_parent()->get_child(0);
	
	sprite = cast_to<AnimatedSprite>(_get_object()->get_node("AnimatedSprite"));
	health_bar = _get_health_bar();
	//sprite->play("idle");
	//_set_special_time(0.5);
}

godot::PlayerShootGhost::~PlayerShootGhost()
{
	sprite = nullptr;
}

void godot::PlayerShootGhost::_move()
{
	PlayerData::_move();

	//String animation_name = sprite->get_animation();
	//if (sprite->get_sprite_frames()->get_animation_loop(animation_name) == false && sprite->get_frame() == sprite->get_sprite_frames()->get_frame_count(animation_name) - 1)
	//	sprite->play("idle");

	//if (PlayerData::_get_dir() == Vector2::ZERO && animation_name != "revive" && animation_name != "damaged")
	//	sprite->play("idle");

	//if (PlayerData::_get_dir() != Vector2::ZERO && sprite->get_animation() == "idle")
	//	sprite->play("run");
}

void godot::PlayerShootGhost::_process_input()
{
	Vector2 dir = Vector2(0, 0);

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
		sprite->set_offset(Vector2(-35, 0));
		//shoot_particles->set_position(Vector2(-11, 0));
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed(move_right))
	{
		sprite->set_flip_h(false);
		sprite->set_offset(Vector2(35, 0));
		//shoot_particles->set_position(Vector2(11, 0));
		dir.x += _get_speed();
	}

	PlayerData::_set_dir(dir);
}

void godot::PlayerShootGhost::_update_health_bar()
{
	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerShootGhost::_get_health_bar()
{
	if (health_bar != nullptr)
		return health_bar;
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P1HealthBarWrapper/ProgressBar"));
}

void godot::PlayerShootGhost::_heal()
{
	_get_object()->call("_ghost_to_player");
}