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

	Enemies::get_singleton()->_remove_player2();

	sprite = cast_to<AnimatedSprite>(obj->get_node("AnimatedSprite"));
	health_bar = _get_health_bar();

	sprite->set_visible(false);

	sprite = cast_to<AnimatedSprite>(obj->get_node("GhostSprite"));

	sprite->set_visible(true);
	sprite->play("show");

	PlayersContainer::_get_instance()->_set_player2_regular(obj);
	PlayersContainer::_get_instance()->_set_player2(nullptr);
	Enemies::get_singleton()->_remove_player2();
}

godot::PlayerMeleeGhost::~PlayerMeleeGhost()
{	
	sprite = nullptr;
}

void godot::PlayerMeleeGhost::_process_input()
{
	Vector2 dir = Vector2(0, 0);

	//move up
	if (input_controller->is_action_pressed(input_map["move_up"]))
		dir.y -= _get_speed();

	//move down
	if (input_controller->is_action_pressed(input_map["move_down"]))
		dir.y += _get_speed();

	//move left
	if (input_controller->is_action_pressed(input_map["move_left"]))
	{
		sprite->set_flip_h(true);
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed(input_map["move_right"]))
	{
		sprite->set_flip_h(false);
		dir.x += _get_speed();
	}

	PlayerData::_set_dir(dir);
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