#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerMeleeDied::PlayerMeleeDied(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
	_change_can_fight(false);
	sprite = cast_to<AnimatedSprite>(obj->get_child(0));
	//sprite->play("idle");

	vfx_sprite = cast_to<AnimatedSprite>(obj->get_node("Area2D3")->get_child(1));

	animator = cast_to<AnimationPlayer>(_get_object()->get_node("AnimationPlayer"));
}

godot::PlayerMeleeDied::~PlayerMeleeDied()
{
	sprite = nullptr;
	vfx_sprite = nullptr;

	animator = nullptr;
}

void godot::PlayerMeleeDied::_revive()
{
	sprite->play("revive");

	PlayerData::_revive();
	PlayersContainer::_get_instance()->_set_player2(_get_object());
}

void godot::PlayerMeleeDied::_update_health_bar()
{
	auto health_bar = _get_health_bar();

	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerMeleeDied::_get_health_bar()
{
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P2HealthBarWrapper/ProgressBar"));
}