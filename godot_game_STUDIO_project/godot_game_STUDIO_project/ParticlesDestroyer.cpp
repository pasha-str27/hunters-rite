#include "ParticlesDestroyer.h"

using namespace godot;

void godot::ParticlesDestroyer::_register_methods()
{
	register_method("_ready", &ParticlesDestroyer::_ready);
	register_method("_on_timeout", &ParticlesDestroyer::_on_timeout);

	register_property<ParticlesDestroyer, float>("Wait time", &ParticlesDestroyer::wait_time, 0);
}

void godot::ParticlesDestroyer::_init()
{
}

void godot::ParticlesDestroyer::_ready()
{
	timer = Timer::_new();
	add_child(timer);
	timer->connect("timeout", this, "_on_timeout");
	timer->start(2);
	set_emitting(true);
}

void godot::ParticlesDestroyer::_on_timeout()
{
	queue_free();
}

godot::ParticlesDestroyer::ParticlesDestroyer()
{
}

godot::ParticlesDestroyer::~ParticlesDestroyer()
{
	timer = nullptr;
}
