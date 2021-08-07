#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::CameraShake::CameraShake()
{
	shake_power = 10;
}

godot::CameraShake::~CameraShake()
{
	camera = nullptr;
}

void godot::CameraShake::_register_methods()
{
	register_method("_ready", &CameraShake::_ready);
	register_method("_process", &CameraShake::_process);
	register_method("_start", &CameraShake::_start);
}

void godot::CameraShake::_init()
{
}

void godot::CameraShake::_ready()
{
	camera = cast_to<Camera2D>(get_parent());
	curPos = camera->get_offset();
}

void godot::CameraShake::_start(float power, float duration)
{
	if (!isShake)
	{
		elapsedtime = 0;
		shake_power = power;
		shake_time = duration;
		isShake = true;
	}
}

void godot::CameraShake::_process(float delta)
{
	if (isShake)
		_shake(delta);
}

void godot::CameraShake::_shake(float delta)
{
	if (elapsedtime < shake_time) 
	{
		Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
		rng->randomize();
		camera->set_offset(Vector2(rng->randf(), rng->randf()) * shake_power);
		elapsedtime += delta;
	}	
	else 
	{
		isShake = false;
		elapsedtime = 0;
		camera->set_offset(curPos);
	}	
}

