#pragma once
#include <Godot.hpp>
#include <Sprite.hpp>
#include <Texture.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>

namespace godot 
{
	class texture : public Sprite
	{
	private:
		GODOT_CLASS(texture, Sprite)
	public:
		static void _register_methods();
		void _ready();

		void _init();

		void _process(float delta);

		texture();
		~texture();
	};
}
