#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "IPlayer.h"
#endif

#include <Vector2.hpp>
#include <Input.hpp>
#include <Sprite.hpp>

namespace godot
{
	class Player2 : public godot::IPlayer, public KinematicBody2D
	{
		static Player2* singleton;
		Node2D* object;
		int speed;
		Vector2 dir;
		Input* input_controller;

	private:
		//GODOT_CLASS(Player1, KinematicBody2D);
		Player2(Node2D* obj);

	public:
		~Player2();
		void move();
		void process_input();
		static Player2* get_singleton(Node2D* obj)
		{
			if (singleton == nullptr)
				singleton = new Player2(obj);
			return singleton;
		}
	};
}
