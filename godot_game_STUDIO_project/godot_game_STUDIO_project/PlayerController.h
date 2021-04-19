#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Node.hpp>
#include <OS.hpp>

#include "Player1.h"
#include "Player2.h"

namespace godot
{
	class PlayerController:public KinematicBody2D
	{
	private:
		GODOT_CLASS(PlayerController, KinematicBody2D);
		godot::IPlayer* current_player;

	public:
		static void _register_methods();
		PlayerController();
		~PlayerController();
		void _init();
		void _ready();
		void _process(float delta);
	};
}
