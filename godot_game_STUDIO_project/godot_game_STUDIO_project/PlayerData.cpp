#include "PlayerData.h"

godot::Input* godot::PlayerData::input_controller = nullptr;

godot::PlayerData::PlayerData(Node2D* object)
{
	this->object = object;
	dir = Vector2(0, 0);
	if(input_controller==nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::PlayerData()
{
	dir = Vector2(0, 0);
	if (input_controller == nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::~PlayerData()
{
}

void godot::PlayerData::move()
{
	cast_to<KinematicBody2D>(object)->move_and_slide(dir);
}

void godot::PlayerData::set_speed(float speed)
{
	this->speed = speed;
}

float godot::PlayerData::get_speed()
{
	return speed;
}

void godot::PlayerData::set_dir(Vector2 dir)
{
	this->dir = dir;
}

godot::Node2D* godot::PlayerData::get_object()
{
	return object;
}
