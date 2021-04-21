#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::PlayerController::_register_methods()
{
	register_method((char*)"_process", &PlayerController::_process);
	register_method((char*)"_ready", &PlayerController::_ready);
	register_method((char*)"_input", &PlayerController::_input);
	register_method((char*)"add_bullet", &PlayerController::add_bullet);

	register_property<PlayerController, float>("speed", &PlayerController::speed, 400);
	register_property<PlayerController, Ref<PackedScene>>("bullet_prefab", &PlayerController::bullet_prefab, nullptr);
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
	PlayerProduce* player_producer=nullptr;

	if (get_name() == "Player1")
		player_producer = new ProducePlayer1;

	if (get_name() == "Player2")
		player_producer = new ProducePlayer2;
	
	current_player = player_producer->get_player(this, bullet_prefab);
	current_player->set_speed(speed);
}

void godot::PlayerController::add_bullet(Node* node)
{
	current_player->add_bullet(node);
}

void godot::PlayerController::_input(Input* event)
{
	current_player->process_input();
}

void godot::PlayerController::_process(float delta)
{
	current_player->move();
}
