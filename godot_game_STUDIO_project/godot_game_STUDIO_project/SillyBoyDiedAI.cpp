#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SillyBoyDiedAI::_set_is_player1_onArea(bool value)
{
	is_player1_onArea = value;
	was_setted = true;
}

void godot::SillyBoyDiedAI::_set_is_player2_onArea(bool value)
{
	is_player2_onArea = value;
	was_setted = true;
}

void godot::SillyBoyDiedAI::_set_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_set_is_player1_onArea(true);

	if(player->is_in_group("player2"))
		_set_is_player2_onArea(true);
}

void godot::SillyBoyDiedAI::_remove_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_delete_player1();

	if (player->is_in_group("player2"))
		_delete_player2();

	if (player->is_in_group("player1"))
		_set_is_player1_onArea(false);

	if (player->is_in_group("player2"))
		_set_is_player2_onArea(false);
}

godot::SillyBoyDiedAI::SillyBoyDiedAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	_change_start_parameters();
}

godot::SillyBoyDiedAI::~SillyBoyDiedAI()
{
	directions.clear();
}

void godot::SillyBoyDiedAI::_fight(Node2D* player1, Node2D* player2)
{
	if (!was_setted)
	{
		if (is_player1_onArea && player1 != nullptr)
			player1->call("_take_damage", damage, false);

		if (is_player2_onArea && player2 != nullptr)
			player2->call("_take_damage", damage, false);
	}

	was_setted = false;

	_get_enemy()->call("_start_timer");
}
