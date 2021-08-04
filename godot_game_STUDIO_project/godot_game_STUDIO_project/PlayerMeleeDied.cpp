#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerMeleeDied::PlayerMeleeDied(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
	sprite = cast_to<AnimatedSprite>(obj->get_child(0));
	health_bar = _get_health_bar();

	cast_to<KinematicBody2D>(obj)->set_collision_mask_bit(1, false);
	cast_to<KinematicBody2D>(obj)->set_collision_layer_bit(0, false);
	cast_to<KinematicBody2D>(obj)->set_collision_layer_bit(15, false);
	cast_to<Area2D>(obj->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<Area2D>(obj->get_node("Area2D"))->set_collision_layer_bit(0, false);

	Enemies::get_singleton()->_remove_player2();
	PlayersContainer::_get_instance()->_set_player2_regular(obj);
	PlayersContainer::_get_instance()->_set_player2(nullptr);
}

godot::PlayerMeleeDied::~PlayerMeleeDied()
{
	sprite = nullptr;
}

void godot::PlayerMeleeDied::_revive()
{
	sprite->play("revive");

	PlayerData::_revive();
	PlayersContainer::_get_instance()->_set_player2(_get_object());
}

void godot::PlayerMeleeDied::_update_health_bar()
{
	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerMeleeDied::_get_health_bar()
{
	if (health_bar != nullptr)
		return health_bar;
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P2HealthBarWrapper/ProgressBar"));
}