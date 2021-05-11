#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::FadeAnimation::_register_methods()
{
	register_method("_init", &FadeAnimation::_init);
	register_method("_ready", &FadeAnimation::_ready);
	register_method("_on_timeout", &FadeAnimation::_on_timeout);

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
}

godot::FadeAnimation::FadeAnimation()
{
}

void godot::FadeAnimation::_on_timeout()
{
	Godot::print(animation_name);
	if(animation_name == "fade_in")
		CustomExtensions::GetChildByName(get_node("/root/Node2D/Node/Camera2D"), "EnemySpawner")->call("_prepare_spawn");
	else if(animation_name == "fade_out")
		CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->call("_start_move");
	timer->disconnect("timeout", this, "_on_timeout");
	get_parent()->get_parent()->queue_free();
}
