#include "PlayerController.h"

using namespace godot;

void godot::PlayerController::_register_methods()
{
	register_method((char*)"_process", &PlayerController::_process);
	register_method((char*)"_ready", &PlayerController::_ready);
	register_method((char*)"_input", &PlayerController::_input);
	register_property<PlayerController, float>("speed", &PlayerController::speed, 400);
}

godot::PlayerController::PlayerController()
{	
}

godot::PlayerController::~PlayerController()
{
}

void godot::PlayerController::_init()
{
}

void godot::PlayerController::_ready()
{
	if(get_name()=="Player1")
		current_player = Player1::get_singleton(this);
	if (get_name() == "Player2")
		current_player = Player2::get_singleton(this);

	current_player->set_speed(speed);
}

void godot::PlayerController::_input(Input* event)
{
	current_player->process_input();
}

void godot::PlayerController::_process(float delta)
{
	current_player->move();
}
