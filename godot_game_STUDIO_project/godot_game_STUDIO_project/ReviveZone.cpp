#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::ReviveZone::ReviveZone()
{
	player_is_in_area = false;

	//adding numbers
	for(int i=48;i<=57;++i)
		keys.push_back(i);

	//adding symbols
	for (int i = 65; i <= 90; ++i)
		keys.push_back(i);

	current_key = -1;
	timer = Timer::_new();
}

godot::ReviveZone::~ReviveZone()
{
	keys.clear();
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
}

void godot::ReviveZone::_init()
{
}

void godot::ReviveZone::_ready()
{
	random = RandomNumberGenerator::_new();
	random->randomize();
	add_child(timer);
	timer->connect("timeout", this, "_kill_revive_progress");
	timer->start(0.1);
}

void godot::ReviveZone::_process()
{
}

void godot::ReviveZone::_input(Input* event)
{
	if (!player_is_in_area)
		return;

	if (cast_to<InputEventKey>(event)->get_scancode() == current_key)
	{
		current_key = _generate_key();

		Godot::print("Enter " + OS::get_singleton()->get_scancode_string(current_key));

		cast_to<ProgressBar>(get_child(1))->set_value(cast_to<ProgressBar>(get_child(1))->get_value() + 30);

		if (cast_to<ProgressBar>(get_child(1))->get_value() == 100)
		{
			get_parent()->call("_revive");
			queue_free();
		}
	}
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

	if (current_key == -1)
		current_key = _generate_key();

	Godot::print("Enter " + OS::get_singleton()->get_scancode_string(current_key));
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
	return keys[random->randi_range(0,keys.size()-1)];
}

void godot::ReviveZone::_kill_revive_progress()
{
	cast_to<ProgressBar>(get_child(1))->set_value(cast_to<ProgressBar>(get_child(1))->get_value() - 1);

	timer->disconnect("timeout", this, "_kill_revive_progress");
	timer->connect("timeout", this, "_kill_revive_progress");
	timer->start(0.1);
}