#include <KinematicBody2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>

namespace godot
{
	class IPlayer
	{
	public:
		virtual void process_input() = 0;
		virtual void move() = 0;
		virtual void set_speed(float speed) = 0;
		virtual void fight() = 0;
		virtual void add_bullet(Node* node=nullptr) = 0;
	};
}
