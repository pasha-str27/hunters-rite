#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::AudioEffect::_register_methods()
{
	register_method("_init", &AudioEffect::_init);
	register_method("_ready", &AudioEffect::_ready);
	register_method("_on_time_out", &AudioEffect::_on_time_out);

	register_property<AudioEffect, float>("duration", &AudioEffect::duration, -2);
}

godot::AudioEffect::~AudioEffect()
{
	timer = nullptr;
}

void godot::AudioEffect::_init()
{
}

void godot::AudioEffect::_ready()
{
	timer = Timer::_new();
	add_child(timer);
	timer->connect("timeout", this, "_on_time_out");
	timer->start(duration);
	play();
}

void godot::AudioEffect::_on_time_out()
{
	queue_free();
}