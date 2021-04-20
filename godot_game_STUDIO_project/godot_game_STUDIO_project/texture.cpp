#include "texture.h"

void godot::texture::_register_methods() 
{
	register_method((char*)"_ready", &texture::_ready);
	register_method((char*)"_input", &texture::_input);
	//	register property
	register_property<texture, Particles2D*>("particles", &texture::particles, nullptr);
}

void godot::texture::_init() {}

void godot::texture::_ready()
{
	//	console log
	Godot::print("jdjdf");
	
	particles = cast_to<Particles2D>(get_child(0));
}

void godot::texture::_process(float delta)
{
	
}


void godot::texture::_input(Variant ev) {
	Ref<InputEvent> _event = ev;
	if (_event->is_action_pressed("start_emitting")) {
		particles->set_emitting(true);
	}
	else if (_event->is_action_pressed("end_emitting")) {
		particles->set_emitting(false);
	}
	else if (_event->is_action_pressed("restart_emitting")) {
		particles->restart();
	}
}

godot::texture::~texture()
{
}

godot::texture::texture()
{
	
}

