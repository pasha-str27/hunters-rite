#include "texture.h"

void godot::texture::_register_methods() 
{
	register_method((char*)"_ready", &texture::_ready);
	register_method("on_timeout", &texture::on_timeout);
	//	register property
	register_property<texture, Particles2D*>("particles", &texture::particles, nullptr);
}

void godot::texture::_init() {}

void godot::texture::_ready()
{
	//	console log
	Godot::print("jdjdf");
	
	//particles = cast_to<Particles2D>(get_child(0));
	Godot::print("22");
	some_function();
}

void godot::texture::some_function() {
	timer->connect("timeout", this, "on_timeout");
	timer->set_wait_time(0.5f);
	add_child(timer);
	Godot::print("Timer started");
	timer->start();
}

void godot::texture::on_timeout() {
	Godot::print("Timer ended");
	timer->disconnect("timeout", this, "on_timeout");
}



void godot::texture::_process(float delta)
{
	
}

void godot::texture::_input(Variant ev) {
	Ref<InputEvent> event = ev;
	if (event->is_action_pressed("start_emitting")) {
		particles->set_emitting(true);
	}
	else if (event->is_action_pressed("end_emitting")) {
		particles->set_emitting(false);
	}
	else if (event->is_action_pressed("restart_emitting")) {
		particles->restart();
	}
}

godot::texture::~texture()
{
}

godot::texture::texture()
{
	timer = Timer::_new();

}
