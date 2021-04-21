#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "PlayerData.h"
#endif
#include <Vector2.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>

namespace godot
{
	class Player2 : public PlayerData/*, public KinematicBody2D*/
	{
		static Player2* singleton;

	private:
		Player2(Node2D* obj,Ref<PackedScene>bullet=0);

	public:
		~Player2();
		void move();
		void process_input();
		void fight();
		void add_bullet(Node* node=nullptr);
		static Player2* get_singleton(Node2D* object, Ref<PackedScene>bullet = 0)
		{
			if (singleton == nullptr)
				singleton = new Player2(object);
			return singleton;
		}
		void set_speed(float speed);
	};
}
