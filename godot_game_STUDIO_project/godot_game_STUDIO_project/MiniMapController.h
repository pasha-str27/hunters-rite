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

		Sprite* curr_room = nullptr;
		Sprite* undisc_room = nullptr;
		Sprite* disc_room = nullptr;
		float zoom = 1.5;

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process();

		void _status_checker();

		MiniMapController();
		~MiniMapController();
	};
}