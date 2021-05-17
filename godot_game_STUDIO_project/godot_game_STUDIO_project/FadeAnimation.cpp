#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::FadeAnimation::_register_methods()
{
	register_method("_init", &FadeAnimation::_init);
	register_method("_ready", &FadeAnimation::_ready);
	register_method("_on_timeout", &FadeAnimation::_on_timeout);
	register_method("_set_is_exit_anim", &FadeAnimation::_set_is_exit_anim);

	register_property<FadeAnimation, float>("animation_time", &FadeAnimation::animation_time, -1);
	register_property<FadeAnimation, String>("animation_name", &FadeAnimation::animation_name, "");
}

void godot::FadeAnimation::_init()
{
}

void godot::FadeAnimation::_ready()
{
	set_current_animation(animation_name);
	timer = Timer::_new();
	add_child(timer);
	timer->connect("timeout", this, "_on_timeout");
	timer->start(animation_time);
	Godot::print("anim started");
}

void godot::FadeAnimation::_set_is_exit_anim(bool value)
{
	is_exit_anim = value;
}

void godot::FadeAnimation::_set_is_exit_anim(bool value)
{
	is_exit_anim = value;
}

godot::FadeAnimation::FadeAnimation()
{
}

void godot::FadeAnimation::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	if (!get_node("/root")->has_node("Pause") && !get_node("/root")->has_node("Notice") && !get_node("/root")->has_node("Menu"))
	{
		if (animation_name == "fade_in")
			CustomExtensions::GetChildByName(get_node("/root/Node2D/Node/Camera2D"), "EnemySpawner")->call("_prepare_spawn");
		else if (animation_name == "fade_out")
		{
			if(!is_exit_anim)
				CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->call("_start_move");
			else
				CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "exit")->call("_load_menu_scene");
		}
	}
	get_parent()->get_parent()->queue_free();
}
