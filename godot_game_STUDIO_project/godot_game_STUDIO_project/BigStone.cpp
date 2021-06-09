#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::BigStone::_register_methods()
{
	register_method("_init", &BigStone::_init);
	register_method("_ready", &BigStone::_ready);
	register_method("_add_player", &BigStone::_add_player);
	register_method("_remove_player", &BigStone::_remove_player);
	register_method("_can_heal_true", &BigStone::_can_heal_true);
}

void godot::BigStone::_init()
{
}

void godot::BigStone::_ready()
{
	timer = Timer::_new();
	add_child(timer);
}

void godot::BigStone::_remove_player(Node2D* node)
{
	if (node->is_in_group("player"))
		--players_count;
}

void godot::BigStone::_add_player(Node2D* node)
{
	if (node->is_in_group("player"))
		++players_count;
	
	if(can_heal)
		_hill_players();
}

void godot::BigStone::_hill_players()
{
	auto player_conteiner = PlayersContainer::_get_instance();

	if (MenuButtons::player_name == 3 && (players_count == 2
		|| player_conteiner->_get_player1() == nullptr || player_conteiner->_get_player2() == nullptr))
	{
		if (player_conteiner->_get_player1() != nullptr)
			player_conteiner->_get_player1()->call("_set_HP", (float)player_conteiner->_get_player1()->call("_get_max_HP"));

		if (player_conteiner->_get_player2() != nullptr)
			player_conteiner->_get_player2()->call("_set_HP", (float)player_conteiner->_get_player2()->call("_get_max_HP"));
		
		can_heal = false;
		timer->connect("timeout", this, "_can_heal_true");
		timer->start(heal_cooldown);
	}

	if ((MenuButtons::player_name == 1 || MenuButtons::player_name == 2) && players_count == 1)
	{
		if (player_conteiner->_get_player1() != nullptr)
			player_conteiner->_get_player1()->call("_set_HP", (float)player_conteiner->_get_player1()->call("_get_max_HP"));

		if (player_conteiner->_get_player2() != nullptr)
			player_conteiner->_get_player2()->call("_set_HP", (float)player_conteiner->_get_player2()->call("_get_max_HP"));
		
		can_heal = false;
		timer->connect("timeout", this, "_can_heal_true");
		timer->start(heal_cooldown);
	}
}

void godot::BigStone::_can_heal_true()
{
	timer->disconnect("timeout", this, "_can_heal_true");
	can_heal = true;
	_hill_players();
}
