#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::PoisonEgg::_register_methods()
{
	register_method("_init", &PoisonEgg::_init);
	register_method("_ready", &PoisonEgg::_ready);
	register_method("_on_timer_out", &PoisonEgg::_on_timer_out);
	register_method("_on_player_area_entered", &PoisonEgg::_on_player_area_entered);
	
	register_property<PoisonEgg, Ref<PackedScene>>("destroy particles", &PoisonEgg::destroy_particles, nullptr);
}

void godot::PoisonEgg::_init()
{
}

void godot::PoisonEgg::_ready()
{
	cast_to<Area2D>(get_node("Poison"))->set_collision_layer_bit(0, false);
	cast_to<Area2D>(get_node("Poison"))->set_collision_layer_bit(2, false);
	cast_to<Area2D>(get_node("Poison"))->set_collision_layer_bit(5, false);
	cast_to<Area2D>(get_node("Poison"))->set_collision_mask_bit(0, false);

	start_particles = cast_to<Particles2D>(get_node("StartPoisonEggParticles"));
	start_particles->set_emitting(true);
	add_child(timer);
	cast_to<Node2D>(get_child(0))->set_visible(false);
	timer->connect("timeout", this, "_on_timer_out");
	timer->start(.5f);
}

void godot::PoisonEgg::_on_timer_out()
{
	timer->disconnect("timeout", this, "_on_timer_out");
	start_particles->set_emitting(false);
	cast_to<Node2D>(get_child(0))->set_visible(true);
	cast_to<Area2D>(get_node("Poison"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(get_node("Poison"))->set_collision_layer_bit(2, true);
	cast_to<Area2D>(get_node("Poison"))->set_collision_layer_bit(5, true);
	cast_to<Area2D>(get_node("Poison"))->set_collision_mask_bit(0, true);
}

void godot::PoisonEgg::_on_player_area_entered(Node* node)
{
	if (destroy_particles == nullptr)
	{
		queue_free();
		return;
	}

	if (node->is_in_group("player") || node->is_in_group("player_bullet") || node->is_in_group("sword"))
	{
		_make_destroy_particles();
		queue_free();
	}
}

void godot::PoisonEgg::_make_destroy_particles()
{
	auto destroy = cast_to<Node2D>(destroy_particles->instance());
	get_node("/root/Node2D/Node")->call_deferred("add_child", destroy);
	destroy->set_global_position(this->get_global_position());
}

godot::PoisonEgg::PoisonEgg()
{
	timer = Timer::_new();
	start_particles = nullptr;
	destroy_particles = nullptr;
}

godot::PoisonEgg::~PoisonEgg()
{
	timer = nullptr;
	start_particles = nullptr;
}
