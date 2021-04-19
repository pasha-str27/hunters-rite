#include "IPlayer.h"

namespace godot
{
	class PlayerData : public IPlayer, public KinematicBody2D
	{
		int speed;
		Vector2 dir;
		Node2D* object;

	public:
		PlayerData(Node2D* object);
		PlayerData();
		~PlayerData();
		
		virtual void move();
		virtual void set_speed(float speed);
		float get_speed();
		void set_dir(Vector2 dir);

		Node2D* get_object();

		virtual void process_input() = 0;

		static Input* input_controller;
	};
}