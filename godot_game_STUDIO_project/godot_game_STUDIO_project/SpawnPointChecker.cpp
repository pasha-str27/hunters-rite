#include "SpawnPointChecker.h"

void godot::SpawnPointChecker::_register_methods()
{
	register_method("_on_SpawnPointChecker_area_entered", &SpawnPointChecker::_on_SpawnPointChecker_area_entered);
}

void godot::SpawnPointChecker::_init()
{
}

void godot::SpawnPointChecker::_on_SpawnPointChecker_area_entered(Node* other)
{
	if (other->get_name().find("Checker"))
		get_parent()->queue_free();
	else if (other->get_name().find("Info"))
		get_parent()->queue_free();
	else if (other->get_name().find("Spawner")) {
		String direction = other->call("_get_spawner_direction");
		get_parent()->call("_add_door_direction", direction, 1);
	}
		
}
