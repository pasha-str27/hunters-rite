#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::CameraController::_register_methods()
{
	register_method("_process", &CameraController::_process);
	register_method("_init", &CameraController::_init);
	register_method("_ready", &CameraController::_ready);
	register_method("_input", &CameraController::_input);
}

void godot::CameraController::_init()
{
}

void godot::CameraController::_ready()
{
	player1 = cast_to<Node2D>(get_node("/root/Node2D/Node/Player1"));
	player2 = cast_to<Node2D>(get_node("/root/Node2D/Node/Player2"));
}

void godot::CameraController::_process()
{
}

void godot::CameraController::_input(InputEvent* event)
{
	if (event->is_action_released("Camera_up"))
	{
		float delta = OS::get_singleton()->get_window_size().y;

		set_global_position(get_global_position() - Vector2(0, delta));		

		player1->set_global_position(player1->get_global_position() - Vector2(0, delta));
		player2->set_global_position(player2->get_global_position() - Vector2(0, delta));
	}

	if (event->is_action_released("Camera_down"))
	{
		float delta = OS::get_singleton()->get_window_size().y;

		set_global_position(get_global_position() + Vector2(0, delta));

		player1->set_global_position(player1->get_global_position() + Vector2(0, delta));
		player2->set_global_position(player2->get_global_position() + Vector2(0, delta));
	}

	if (event->is_action_released("Camera_left"))
	{
		float delta = OS::get_singleton()->get_window_size().x;

		set_global_position(get_global_position() - Vector2(delta, 0));

		player1->set_global_position(player1->get_global_position() - Vector2(delta, 0));
		player2->set_global_position(player2->get_global_position() - Vector2(delta, 0));
	}

	if (event->is_action_released("Camera_right"))
	{
		float delta = OS::get_singleton()->get_window_size().x;

		set_global_position(get_global_position() + Vector2(delta, 0));

		player1->set_global_position(player1->get_global_position() + Vector2(delta, 0));
		player2->set_global_position(player2->get_global_position() + Vector2(delta, 0));
	}
}

godot::CameraController::CameraController()
{
	player1 = nullptr;
	player2 = nullptr;
}

godot::CameraController::~CameraController()
{
}
