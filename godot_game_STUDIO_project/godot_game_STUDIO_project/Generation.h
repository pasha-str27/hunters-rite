#pragma once
#include <Godot.hpp>
#include <PackedScene.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <Tree.hpp>
#include <Array.hpp>
#include <OS.hpp>

namespace godot
{
	class Generation: public Node
	{
	private:
		GODOT_CLASS(Generation, Node);
	public:
		static void _register_methods();
		void _ready();
		//	decleared property
		Array spritePrefab{};

		void _init();

		void _process(float delta);

		void _input(Variant ev);

		Generation();
		~Generation();
	};
}
