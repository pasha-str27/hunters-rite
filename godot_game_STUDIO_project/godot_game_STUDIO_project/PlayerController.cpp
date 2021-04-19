#include "PlayerController.h"

using namespace godot;

void godot::PlayerController::_register_methods()
{
	register_method((char*)"_process", &PlayerController::_process);
	register_method((char*)"_ready", &PlayerController::_ready);
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
}

void godot::PlayerController::_process(float delta)
{
	current_player->process_input();
	//if(get_global_position().x>0&&get_global_position().x<get_viewport_rect().get_size().width
	//	&& get_global_position().y>0 && get_global_position().y < get_viewport_rect().get_size().height)
			current_player->move();
}
