#include "Destroyer.h"

void godot::Destroyer::_init()
{
}

void godot::Destroyer::_ready()
{
}

void godot::Destroyer::_register_methods()
{
	register_method("_ready", &Destroyer::_ready);
	register_method("_on_Destroyer_area_entered", &Destroyer::_on_Destroyer_area_entered);
}

void godot::Destroyer::_on_Destroyer_area_entered(Node *other)
{
	if (other->get_name().find("Spawner") != -1)
		other->queue_free();
	else if (other->get_name().find("Destroyer") != -1)
		get_parent()->queue_free();
	
}


godot::Destroyer::Destroyer()
{
}


godot::Destroyer::~Destroyer()
{
}
