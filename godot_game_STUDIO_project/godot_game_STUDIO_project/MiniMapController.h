#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class MiniMapController : public MarginContainer
	{
	private:
		GODOT_CLASS(MiniMapController, MarginContainer);

		Texture* curr_room = nullptr;
		Sprite* undisc_room = nullptr;
		Sprite* disc_room = nullptr;

		TextureRect* grid = nullptr;

		std::vector<Vector2> rooms_positions;

		float zoom = 1.5;
		float step_x = 1024;
		float step_y = 720;

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();

		

		MiniMapController();
		~MiniMapController();
	};
}