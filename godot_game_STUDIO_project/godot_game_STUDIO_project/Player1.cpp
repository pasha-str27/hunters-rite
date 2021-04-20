#include "Player1.h"

godot::Player1* godot::Player1::singleton = nullptr;

godot::Player1::Player1(Node2D*obj)
{
	object = obj;
	dir = Vector2(0, 0);
	speed = 500;
	input_controller = Input::get_singleton();
}

godot::Player1::~Player1()
{
}

void godot::Player1::move()
{
	cast_to<KinematicBody2D>(object)->move_and_slide(dir);
}

void godot::Player1::process_input() 
{
	dir = Vector2(0, 0);

	//move up
	if (input_controller->is_key_pressed(16777232))
	{
		dir.y -= speed;
	}
	
	//move down
	if (input_controller->is_key_pressed(16777234))
	{
		
		dir.y += speed;
	}
	
	//move left
	if (input_controller->is_key_pressed(16777231))
	{
		cast_to<Sprite>(object->get_child(0)->get_child(0))->set_flip_h(false);
		dir.x -= speed;
	}

	//move right	
	if (input_controller->is_key_pressed(16777233))
	{
		cast_to<Sprite>(object->get_child(0)->get_child(0))->set_flip_h(true);
		dir.x += speed;
	}
}
