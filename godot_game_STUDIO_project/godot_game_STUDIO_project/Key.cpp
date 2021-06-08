#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Key::_register_methods()
{
	register_method("_init", &Key::_init);
	register_method("_get_type", &Key::_get_type);

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

godot::Key::Key()
{
	key_type = "";
}

godot::Key::~Key()
{
}
