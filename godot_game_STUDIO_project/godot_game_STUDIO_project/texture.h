#pragma once
#include <Godot.hpp>
#include <Particles2D.hpp>
#include <Timer.hpp>
#include <InputEvent.hpp>
#include <ItemList.hpp>

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
		Timer* timer = nullptr;

		void _init();

		void _process(float delta);

		void _input(Variant event);

		void on_timeout();
		void some_function();

		texture();
		~texture();
	};
}
