#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "IPlayer.h"
#endif
#include <Vector2.hpp>
#include <Input.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>
#include <Node.hpp>
#include <Node2D.hpp>

namespace godot
{
	class Player1  : public godot::IPlayer, public KinematicBody2D
	{
		 static Player1* singleton;
		 Node2D* object;
		 int speed;
		 Vector2 dir;
		 Input* input_controller;

	private:
		//GODOT_CLASS(Player1, KinematicBody2D);
		Player1(Node2D* obj);

	public:
		~Player1();
		void move();
		void process_input();
		static Player1* get_singleton(Node2D* obj)
		{
			if (singleton == nullptr)
				singleton = new Player1(obj);
			return singleton;
		}
	};
}
