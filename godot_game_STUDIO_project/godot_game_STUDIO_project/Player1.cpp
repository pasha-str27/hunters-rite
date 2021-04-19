#include "Player1.h"

godot::Player1* godot::Player1::singleton = nullptr;

godot::Player1::Player1(Node2D* obj):PlayerData(obj)
{
}

godot::Player1::~Player1()
{
}

void godot::Player1::move()
{
	PlayerData::move();
}

void godot::Player1::process_input()
{
	Vector2 dir = Vector2(0, 0);

	//move up
	if (input_controller->is_action_pressed("Player1_up"))
	{
		dir.y -= get_speed();
	}

	//move down
	if (input_controller->is_action_pressed("Player1_down"))
	{
		dir.y += get_speed();
	}

	//move left
	if (input_controller->is_action_pressed("Player1_left"))
	{
		cast_to<Sprite>(get_object()->get_child(0)->get_child(0))->set_flip_h(false);
		dir.x -= get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed("Player1_right"))
	{
		cast_to<Sprite>(get_object()->get_child(0)->get_child(0))->set_flip_h(true);
		dir.x += get_speed();
	}
	
	PlayerData::set_dir(dir);
}

void godot::Player1::set_speed(float speed)
{
	PlayerData::set_speed(speed);
}
