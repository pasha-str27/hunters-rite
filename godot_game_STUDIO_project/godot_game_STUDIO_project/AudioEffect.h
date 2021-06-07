#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class AudioEffect :	public AudioStreamPlayer2D
	{
		GODOT_CLASS(AudioEffect, AudioStreamPlayer2D);

		float duration;
		Timer* timer;
	public:
		static void _register_methods();
		AudioEffect();
		~AudioEffect();
		void _init();
		void _ready();
		void _on_time_out();
	};
}