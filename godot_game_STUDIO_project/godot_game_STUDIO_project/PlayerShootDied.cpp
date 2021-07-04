#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerShootDied::PlayerShootDied(Node2D* object, Ref<PackedScene> bullet) : PlayerData(object)
{
	auto node = _get_object()->get_parent()->get_child(0);
	
	sprite = cast_to<AnimatedSprite>(_get_object()->get_node("AnimatedSprite"));
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
	auto health_bar = _get_health_bar();

	Godot::print(_get_HP());

	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerShootDied::_get_health_bar()
{
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P1HealthBarWrapper/ProgressBar"));
}