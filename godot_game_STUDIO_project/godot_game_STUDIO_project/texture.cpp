#include "texture.h"

void godot::texture::_register_methods() 
{
	register_method((char*)"_ready", &texture::_ready);
	register_property<texture, Ref<PackedScene>>("prefab", &texture::spritePrefab, nullptr);
}

void godot::texture::_init() {}

void godot::texture::_ready()
{
	Godot::print("jdjdf");
	
	auto tt = ResourceLoader::get_singleton()->load("res://skull.png");
	set_texture(tt);
	//set_flip_v(true);

	//add_child(cast_to<Sprite>(spritePrefab->instance()));

}

void godot::texture::_process(float delta)
{
	//add_child(cast_to<Sprite>(spritePrefab->instance()));
}

godot::texture::~texture()
{
}

godot::texture::texture()
{
	spritePrefab = nullptr;
}
