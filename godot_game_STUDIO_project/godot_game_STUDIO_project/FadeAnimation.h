#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class FadeAnimation : public AnimationPlayer
	{
		GODOT_CLASS(FadeAnimation, AnimationPlayer);

		float animation_time;
		String animation_name;
		Timer* timer;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		FadeAnimation();
		void _on_timeout();
	};
}