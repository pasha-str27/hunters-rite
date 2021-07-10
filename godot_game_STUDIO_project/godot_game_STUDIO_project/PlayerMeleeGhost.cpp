#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerMeleeGhost::PlayerMeleeGhost(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
	cast_to<KinematicBody2D>(obj)->set_collision_mask_bit(1, false);
	cast_to<KinematicBody2D>(obj)->set_collision_layer_bit(0, false);
	cast_to<KinematicBody2D>(obj)->set_collision_layer_bit(15, false);
	cast_to<Area2D>(obj->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<Area2D>(obj->get_node("Area2D"))->set_collision_layer_bit(0, false);
	_change_can_fight(false);
	sprite = cast_to<AnimatedSprite>(obj->get_child(0));
	//sprite->play("idle");

	vfx_sprite = cast_to<AnimatedSprite>(obj->get_node("Area2D3")->get_child(1));

	animator = cast_to<AnimationPlayer>(_get_object()->get_node("AnimationPlayer"));
	 health_bar = _get_health_bar();
	//_set_special_time(1.5);
}

godot::PlayerMeleeGhost::~PlayerMeleeGhost()
{	
	sprite = nullptr;
	vfx_sprite = nullptr;
	animator = nullptr;
}

void godot::PlayerMeleeGhost::_move()
{
	PlayerData::_move();

	//String animation_name = sprite->get_animation();
	//if (sprite->get_sprite_frames()->get_animation_loop(animation_name) == false 
	//	&& sprite->get_frame() == sprite->get_sprite_frames()->get_frame_count(animation_name) - 1) 
	//{
	//	sprite->set_offset(Vector2::ZERO);
	//	sprite->play("idle");
	//}

	//if (PlayerData::_get_dir() == Vector2::ZERO && animation_name != "revive" 
	//	&& animation_name != "damaged" && animation_name != "attack")
	//		sprite->play("idle");

	//if (PlayerData::_get_dir() != Vector2::ZERO && sprite->get_animation() == "idle")
	//	sprite->play("run");

	//if (sprite->is_flipped_h() && sprite->get_animation() == "attack")
	//	sprite->set_offset(Vector2(-26, -4));
	//else 
	//	if (!sprite->is_flipped_h() && sprite->get_animation() == "attack")
	//		sprite->set_offset(Vector2(26, -4));
}

void godot::PlayerMeleeGhost::_process_input()
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
		_get_object()->call("_flip_ghost", true);
		sprite->set_flip_h(true);
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed(move_right))
	{
		_get_object()->call("_flip_ghost", false);
		sprite->set_flip_h(false);
		dir.x += _get_speed();
	}

	PlayerData::_set_dir(dir);
}

void godot::PlayerMeleeGhost::_set_HP(float value)
{
	PlayerData::_set_HP(value);

	if (_get_HP() <= 0)
	{
		Enemies::get_singleton()->_remove_player2();
		PlayersContainer::_get_instance()->_set_player2(nullptr);

		if (_was_revived())
		{
			_get_object()->queue_free();
			return;
		}
		
		_get_object()->call("_die");
	}
}

void godot::PlayerMeleeGhost::_heal()
{
	_get_object()->call("_ghost_to_player");
}

void godot::PlayerMeleeGhost::_update_health_bar()
{
	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerMeleeGhost::_get_health_bar()
{
	if (health_bar != nullptr)
		return health_bar;
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P2HealthBarWrapper/ProgressBar"));
}