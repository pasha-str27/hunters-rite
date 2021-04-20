#include <KinematicBody2D.hpp>
#include <Godot.hpp>

namespace godot
{
	class IPlayer
	{
	public:
		virtual void process_input() = 0;
		virtual void move() = 0;
	};
}
