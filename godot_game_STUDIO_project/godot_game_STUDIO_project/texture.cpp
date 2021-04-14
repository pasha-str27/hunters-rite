#include "texture.h"

void godot::texture::_register_methods() 
{
	register_method((char*)"_ready", &texture::_ready);
}

void godot::texture::_init() {}

void godot::texture::_ready()
{
	Godot::print("jdjdf");
	set_flip_v(true);
}

void godot::texture::_process(float delta)
{
}

godot::texture::~texture()
{
}

godot::texture::texture()
{
}
