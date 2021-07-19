#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerShootDied::PlayerShootDied(Node2D* object, Ref<PackedScene> bullet) : PlayerData(object)
{
	health_bar = _get_health_bar();
	auto node = _get_object()->get_parent()->get_child(0);
	
	sprite = cast_to<AnimatedSprite>(_get_object()->get_node("AnimatedSprite"));

	cast_to<KinematicBody2D>(object)->set_collision_mask_bit(1, false);
	cast_to<KinematicBody2D>(object)->set_collision_layer_bit(0, false);
	cast_to<KinematicBody2D>(object)->set_collision_layer_bit(15, false);
	cast_to<Area2D>(object->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<Area2D>(object->get_node("Area2D"))->set_collision_layer_bit(0, false);
}

godot::PlayerShootDied::~PlayerShootDied()
{
	sprite = nullptr;
}

void godot::PlayerShootDied::_revive()
{
	sprite->play("revive");

	PlayerData::_revive();
	PlayersContainer::_get_instance()->_set_player1(_get_object());
}

void godot::PlayerShootDied::_update_health_bar()
{
	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerShootDied::_get_health_bar()
{
	if (health_bar != nullptr)
		return health_bar;
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P1HealthBarWrapper/ProgressBar"));
}