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
	if(input_controller == nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::PlayerData()
{
	HP = 100;
	dir = Vector2(0, 0);
	if (input_controller == nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::~PlayerData()
{
	delete object;
}

void godot::PlayerData::_move()
{
	cast_to<KinematicBody2D>(object)->move_and_slide(dir);
}

void godot::PlayerData::_dash()
{
	if (is_dashing == true)
	{
		speed /= 2;
		_set_dash_state(false);
		
	}
	else
	{
		speed *= 2;
		_set_dash_state(true);
	}
}

void godot::PlayerData::_set_dash_state(bool state)
{
	this->is_dashing = state;
}

bool godot::PlayerData::_get_dash_state()
{
	return is_dashing;
}

void godot::PlayerData::_set_speed(float speed)
{
	this->speed = speed;
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

void godot::PlayerData::_take_damage(float damage)
{
	HP -= damage;

	object->set_global_position(object->get_global_position() - dir.normalized() * damage*5);

	if (HP <= 0)
		object->queue_free();
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
	this->HP = HP;
}
