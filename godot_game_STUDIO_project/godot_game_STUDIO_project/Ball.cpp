#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Ball::_register_methods()
{
	register_method("_init", &Ball::_init);
	register_method("_ready", &Ball::_ready);
	register_method("_connect", &Ball::_connect);
}

void godot::Ball::_init()
{
}

void godot::Ball::_ready()
{
}

void godot::Ball::_connect(Node* node)
{
	auto pos = get_global_position();
	get_parent()->remove_child(this);
	set_block_signals(true);
	node->call_deferred("add_child",this);
	//set_global_position(pos);
}
