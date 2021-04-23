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
	register_method((char*)"_add_bullet", &PlayerController::_add_bullet);
	register_method((char*)"_on_timeout", &PlayerController::_on_timeout);
	register_method((char*)"_start_timer", &PlayerController::_start_timer);
	register_method((char*)"_can_fight", &PlayerController::_can_fight);
	register_method((char*)"_set_enemy", &PlayerController::_set_enemy);

	register_property<PlayerController, float>("speed", &PlayerController::speed, 400);
	register_property<PlayerController, Ref<PackedScene>>("bullet_prefab", &PlayerController::bullet_prefab, nullptr);
}

godot::PlayerController::PlayerController()
{	
	timer = Timer::_new();
}

godot::PlayerController::~PlayerController()
{
	delete current_player;
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
	
	current_player = player_producer->_get_player(this, bullet_prefab);
	current_player->_set_speed(speed);
}

void godot::PlayerController::_start_timer()
{
	timer->connect("timeout", this, "_on_timeout");

	if(!has_node(NodePath(timer->get_name())))
		add_child(timer);

	timer->set_wait_time(0.4);
	timer->start();
}

void godot::PlayerController::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	current_player->_change_can_fight(true);

	if (get_name() == "Player2")
		cast_to<Node2D>(get_child(1))->set_visible(false);
}

bool godot::PlayerController::_can_fight()
{
	return current_player->_can_fight();
}

void godot::PlayerController::_set_enemy(Node* enemy)
{
	current_player->_set_enemy(enemy);
}

void godot::PlayerController::_add_bullet(Node* node)
{
	current_player->_add_bullet(node);
}

void godot::PlayerController::_input(Input* event)
{
	current_player->_process_input();
}

void godot::PlayerController::_process(float delta)
{
	current_player->_move();
}