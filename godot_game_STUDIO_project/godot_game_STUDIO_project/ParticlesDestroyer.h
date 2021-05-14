#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class ParticlesDestroyer: public Particles2D
	{
	private:
		GODOT_CLASS(ParticlesDestroyer, Particles2D);
		Timer* timer = nullptr;
		float wait_time = 2;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_timeout();
		ParticlesDestroyer();
		~ParticlesDestroyer();
	};
}

