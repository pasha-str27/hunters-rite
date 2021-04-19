#include "Player2.h"

godot::Player2* godot::Player2::singleton = nullptr;

godot::Player2::Player2(Node2D* obj)
{
	object = obj;
	dir = Vector2(0, 0);
	speed = 500;
	input_controller = Input::get_singleton();
}

godot::Player2::~Player2()
{
}

void godot::Player2::move()
{
	//if(object->get_tra)
	cast_to<KinematicBody2D>(object)->move_and_slide(dir);
}

void godot::Player2::process_input()
{
	dir = Vector2(0, 0);

	//move up
	if (input_controller->is_key_pressed(87))
	{
		dir.y -= speed;
	}

	//move down
	if (input_controller->is_key_pressed(83))
	{
		dir.y += speed;
	}

	//move left
	if (input_controller->is_key_pressed(65))
	{
		cast_to<Sprite>(object->get_child(0)->get_child(0))->set_flip_h(false);
		dir.x -= speed;
	}

	//move right	
	if (input_controller->is_key_pressed(68))
	{
		cast_to<Sprite>(object->get_child(0)->get_child(0))->set_flip_h(true);
		dir.x += speed;
	}
}
