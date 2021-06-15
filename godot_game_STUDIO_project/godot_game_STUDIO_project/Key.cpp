#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Key::_register_methods()
{
	register_method("_init", &Key::_init);
	register_method("_get_type", &Key::_get_type);
	register_method("_on_Area2D_body_entered", &Key::_on_Area2D_body_entered);
	
	register_property<Key, String>("key_type", &Key::key_type, "");
}

void godot::Key::_init()
{
}

void godot::Key::_ready()
{
}

String godot::Key::_get_type()
{
	return key_type;
}

void godot::Key::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("player"))
	{
		PlayersContainer::_get_instance()->_add_key(_get_type());
		queue_free();
	}
}

godot::Key::Key()
{
	key_type = "";
}

godot::Key::~Key()
{
}
