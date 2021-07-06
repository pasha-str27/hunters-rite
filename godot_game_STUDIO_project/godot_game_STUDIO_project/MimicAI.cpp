#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::MimicAI::MimicAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	can_damage = true;
	damage = 10;
}

godot::MimicAI::~MimicAI()
{

}

void godot::MimicAI::_set_speed(float value)
{
}

void godot::MimicAI::_process(float delta)
{
	if(can_damage)
		_fight(_get_player1(), _get_player2());
}

void godot::MimicAI::change_can_fight(bool value)
{
	can_damage = value;
}

void godot::MimicAI::_fight(Node2D* player1, Node2D* player2)
{
	can_damage = false;
	if (was_setted)
	{
		if (is_player1_onArea && player1 != nullptr) {
			_get_enemy()->call("_change_animation", "attack", 1.5f);
			player1->call("_take_damage", damage, false);
		}

		if (is_player2_onArea && player2 != nullptr)
		{
			_get_enemy()->call("_change_animation", "attack", 1.5f);
			player2->call("_take_damage", damage, false);
		}

	}

	was_setted = false;

	_get_enemy()->call("_start_fixed_timer", 0.1f);
}

void godot::MimicAI::_set_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_set_is_player1_onArea(true);

	if (player->is_in_group("player2"))
		_set_is_player2_onArea(true);
}

void godot::MimicAI::_remove_player(Node2D* player)
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

void godot::MimicAI::_set_is_player1_onArea(bool value)
{
	is_player1_onArea = value;
	was_setted = true;
}

void godot::MimicAI::_set_is_player2_onArea(bool value)
{
	is_player2_onArea = value;
	was_setted = true;
}
