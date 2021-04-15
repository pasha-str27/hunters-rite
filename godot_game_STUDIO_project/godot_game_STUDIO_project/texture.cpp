#include "texture.h"

void godot::texture::_register_methods() 
{
	register_method((char*)"_ready", &texture::_ready);
	//	register property
	register_property<texture, Ref<PackedScene>>("prefab", &texture::spritePrefab, nullptr);
}

void godot::texture::_init() {}

void godot::texture::_ready()
{
	//	console log
	Godot::print("jdjdf");
	
	//	loading ref texture from assets
	auto tt = ResourceLoader::get_singleton()->load("res://skull.png");

	//	setting texture
	set_texture(tt);

	//	flip vertical
	//set_flip_v(true);

	//	instantiating prefabs
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			//	instantiating sprite 
			Sprite* sp = cast_to<Sprite>(spritePrefab->instance());
			//	adding to scene 
			add_child(sp);
			//	transforming created prefab
			sp->set_position(Vector2(j * 64, i * 64));
		}

	}
	//	setting sorting layer
	//sp->set_z_index(-5);
}

void godot::texture::_process(float delta)
{
	
}

godot::texture::~texture()
{
}

godot::texture::texture()
{
	spritePrefab = nullptr;
}
