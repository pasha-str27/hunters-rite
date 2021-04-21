#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Player2* godot::Player2::singleton = nullptr;

godot::Player2::Player2(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
}

godot::Player2::~Player2()
{
}

void godot::Player2::move()
{
	PlayerData::move();
}

void godot::Player2::process_input()
{
	Vector2 dir = Vector2(0, 0);

	//move up
	if (input_controller->is_action_pressed("Player2_up"))
	{
		dir.y -= get_speed();
	}

	//move down
	if (input_controller->is_action_pressed("Player2_down"))
	{
		dir.y += get_speed();
	}

	//move left
	if (input_controller->is_action_pressed("Player2_left"))
	{
		cast_to<Sprite>(get_object()->get_child(0)->get_child(0))->set_flip_h(false);
		dir.x -= get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed("Player2_right"))
	{
		cast_to<Sprite>(get_object()->get_child(0)->get_child(0))->set_flip_h(true);
		dir.x += get_speed();
	}

	PlayerData::set_dir(dir);
}

void godot::Player2::fight()
{
}

void godot::Player2::add_bullet(Node* node)
{
}

void godot::Player2::set_speed(float speed)
{
	PlayerData::set_speed(speed);
}