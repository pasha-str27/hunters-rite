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
	can_heal = true;
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
		_heal_players();
}

void godot::BigStone::_heal_players()
{
	auto player_conteiner = PlayersContainer::_get_instance();

	if (MenuButtons::player_name == 0 && players_count == 2)
	{
		if (player_conteiner->_get_player1_regular() != nullptr)
			_heal_player(player_conteiner->_get_player1_regular());
		if (player_conteiner->_get_player2_regular()->has_method("_heal"))
			_heal_player(player_conteiner->_get_player2_regular());
		
		can_heal = false;
		timer->connect("timeout", this, "_can_heal_true");
		timer->start(heal_cooldown);
	}

	if ((MenuButtons::player_name == 1 || MenuButtons::player_name == 2) && players_count == 1)
	{
		if (player_conteiner->_get_player1_regular() != nullptr)
			_heal_player(player_conteiner->_get_player1_regular());

		if (player_conteiner->_get_player2_regular() != nullptr)
			_heal_player(player_conteiner->_get_player2_regular());
		
		can_heal = false;
		timer->connect("timeout", this, "_can_heal_true");
		timer->start(heal_cooldown);
	}
}

void godot::BigStone::_heal_player(Node2D* player)
{
	if (player->has_method("_heal"))
	{
		player->call_deferred("_heal");
		return;
	}

	for (int i = 0; i < player->get_child_count(); ++i)
		if (player->get_child(i)->has_method("_heal"))
		{
			player->get_child(i)->call_deferred("_heal");
			return;
		}
}

void godot::BigStone::_can_heal_true()
{
	timer->disconnect("timeout", this, "_can_heal_true");
	can_heal = true;
	_heal_players();
}
