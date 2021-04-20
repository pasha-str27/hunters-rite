#pragma once
#include <Godot.hpp>
#include <Sprite.hpp>
#include <Texture.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <Particles2D.hpp>
#include <InputEvent.hpp>

namespace godot 
{
	class texture : public Node2D
	{
	private:
		GODOT_CLASS(texture, Node2D)
	public:
		static void _register_methods();
		void _ready();
		//	decleared property
		Particles2D* particles = nullptr;

		void _init();

		void _process(float delta);

		void _input(Variant event);

		texture();
		~texture();
	};
}
