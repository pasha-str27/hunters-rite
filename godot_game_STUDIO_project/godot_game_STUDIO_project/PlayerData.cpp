#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Input* godot::PlayerData::input_controller = nullptr;

godot::PlayerData::PlayerData(Node2D* object, Ref<PackedScene> bullet)
{
	this->object = object;
	dir = Vector2(0, 0);
	HP = 100;
	max_HP = 100;
	damage = 25;
	was_revived = false;
	can_fight_value = true;
	speed = 250;

	if(input_controller==nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::PlayerData()
{
	object = nullptr;
	HP = 100;
	dir = Vector2(0, 0);
	was_revived = false;
	max_HP = 100;
	damage = 25;
	speed = 250;
	can_fight_value = true;

	if (input_controller == nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::~PlayerData()
{
	//delete object;
}

void godot::PlayerData::_move()
{
	cast_to<KinematicBody2D>(object)->move_and_slide(dir);
}

void godot::PlayerData::_set_speed(float speed)
{
	this->speed = speed > 0 ? speed : 0;
}

float godot::PlayerData::_get_speed()
{
	return speed;
}

void godot::PlayerData::_set_dir(Vector2 dir)
{
	this->dir = dir;
}

godot::Vector2 godot::PlayerData::_get_dir()
{
	return dir.normalized();
}

godot::Node2D* godot::PlayerData::_get_object()
{
	return object;
}

void godot::PlayerData::_take_damage(float damage, bool is_spike)
{
	HP = (HP - damage > 0) ? HP - damage : 0;

	if(is_spike)
		object->set_global_position(object->get_global_position() - dir.normalized() * damage*2);
}

void godot::PlayerData::_change_can_fight(bool value)
{
	can_fight_value = value;
}

bool godot::PlayerData::_can_fight()
{
	return can_fight_value;
}

float godot::PlayerData::_get_HP()
{
	return HP;
}

void godot::PlayerData::_set_HP(float HP)
{
	this->HP = HP > 10 ? HP : 10;
	this->HP = HP > max_HP ? max_HP : HP;
}

float godot::PlayerData::_get_damage()
{
	return damage;
}

void godot::PlayerData::_set_damage(float value)
{
	damage = value > 0 ? value : 0;
}

void godot::PlayerData::_revive()
{
	was_revived = true;
}

bool godot::PlayerData::_was_revived()
{
	return was_revived;
}

float godot::PlayerData::_get_max_HP()
{
	return max_HP;
}

void godot::PlayerData::_set_max_HP(float value)
{
	max_HP += value > 0 ? value : 0;
	this->HP += value;
}
