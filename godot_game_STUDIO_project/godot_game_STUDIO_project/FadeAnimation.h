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
		bool is_exit_anim = false;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _set_is_exit_anim(bool);
		FadeAnimation();
		void _on_timeout();
	};
}