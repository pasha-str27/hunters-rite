#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::ReviveZone::ReviveZone()
{
	player_is_in_area = false;

	keys = new InputReviveManager;

	random = nullptr;

	arrow = nullptr;

	current_key = -1;
	timer = Timer::_new();
}

godot::ReviveZone::~ReviveZone()
{
	arrow = nullptr;
	if(keys!=nullptr)
		delete keys;
	keys = nullptr;
	timer = nullptr;
}

void godot::ReviveZone::_register_methods()
{
	register_method("_init", &ReviveZone::_init);
	register_method("_ready", &ReviveZone::_ready);
	register_method("_input", &ReviveZone::_input);
	register_method("_process", &ReviveZone::_process);
	register_method("_on_revive_zone_body_entered", &ReviveZone::_on_revive_zone_body_entered);
	register_method("_on_revive_zone_body_exited", &ReviveZone::_on_revive_zone_body_exited);
	register_method("_kill_revive_progress", &ReviveZone::_kill_revive_progress);
	register_method("_update_arrow_direction", &ReviveZone::_update_arrow_direction);
}

void godot::ReviveZone::_init()
{
}

void godot::ReviveZone::_ready()
{
	arrow = cast_to<Sprite>(CustomExtensions::GetChildByName(get_node("ProgressBar"), "Arrow"));

	add_child(timer);
	timer->connect("timeout", this, "_kill_revive_progress");
	timer->start(0.1);

	if (get_parent()->is_in_group("player1"))
	{
		keys->_set_player1_buttons();
		_update_arrow_direction();		
		return;
	}

	keys->_set_player2_buttons();

	_update_arrow_direction();
}

void godot::ReviveZone::_process()
{
}

void godot::ReviveZone::_input(Input* _event)
{
	if (!player_is_in_area)
		return;

	if (Input::get_singleton()->is_action_just_released(keys->_get_current_key()))
	{
		keys->_generate_new_key();

		cast_to<ProgressBar>(get_child(1))->set_value(cast_to<ProgressBar>(get_child(1))->get_value() + 30);

		if (cast_to<ProgressBar>(get_child(1))->get_value() == 100)
		{
			get_parent()->call("_revive");
			queue_free();
		}
	}

	_update_arrow_direction();
}

void godot::ReviveZone::_on_revive_zone_body_entered(Node* node)
{
	if (!node->is_in_group("player"))
		return;

	if (node->get_name() == get_parent()->get_name())
		return;

	node->call("_change_can_fight", false);

	player_is_in_area = true;

	set_visible(true);
}

void godot::ReviveZone::_on_revive_zone_body_exited(Node* node)
{
	if (!node->is_in_group("player"))
		return;

	node->call("_change_can_fight", true);
	player_is_in_area = false;

	set_visible(false);
}

int godot::ReviveZone::_generate_key()
{
	return 0;
}

void godot::ReviveZone::_kill_revive_progress()
{
	cast_to<ProgressBar>(get_child(1))->set_value(cast_to<ProgressBar>(get_child(1))->get_value() - 1);

	timer->disconnect("timeout", this, "_kill_revive_progress");
	timer->connect("timeout", this, "_kill_revive_progress");
	timer->start(0.1);
}

void godot::ReviveZone::_update_arrow_direction()
{
	auto current_key = keys->_get_current_key();

	if (current_key == "Player1_right" || current_key == "Player2_right")
	{
		arrow->set_rotation_degrees(90);
		return;
	}

	if (current_key == "Player1_down" || current_key == "Player2_down")
	{
		arrow->set_rotation_degrees(180);
		return;
	}

	if (current_key == "Player1_left" || current_key == "Player2_left")
	{
		arrow->set_rotation_degrees(270);
		return;
	}

	arrow->set_rotation_degrees(0);
}