#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::TutorialEnemy::_register_methods()
{
	register_method("_ready", &TutorialEnemy::_ready);
	register_method("_take_damage", &TutorialEnemy::_take_damage);
	register_method("_on_damage_animation_finished", &TutorialEnemy::_on_damage_animation_finished);
	register_method("_on_spawn_end", &TutorialEnemy::_on_spawn_end);
	

	register_property<TutorialEnemy, float>("HP", &TutorialEnemy::_hp, 100);
}

void godot::TutorialEnemy::_init()
{
}

void godot::TutorialEnemy::_ready()
{
	sprite = cast_to<AnimatedSprite>(find_node("Sprite"));
	health_bar = cast_to<ProgressBar>(get_node("HealthBar"));
	Enemies::get_singleton()->_set_enemy_count(1);

	sprite->set_visible(false);
	health_bar->set_visible(false);

	//	set healthbar values
	health_bar->set_max(_hp);
	health_bar->set_value(_hp);

	cast_to<Area2D>(get_node("Area2D"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(get_node("Area2D"))->set_collision_mask_bit(0, true);
	this->set_collision_mask_bit(9, true);
	this->set_collision_layer_bit(2, true);

	cast_to<Particles2D>(get_node("SpawnParticles"))->set_emitting(true);
	add_child(timer);

	timer->connect("timeout", this, "_on_spawn_end");
	timer->start(.15f);
}

void godot::TutorialEnemy::_take_damage(float damage, int player_id)
{
	if (_hp <= 0)
		return;

	_hp -= damage;
	health_bar->set_value(_hp);

	if (_hp > 0)
	{
		sprite->play("damaged");
		if(!sprite->is_connected("animation_finished", this, "_on_damage_animation_finished"))
			sprite->connect("animation_finished", this, "_on_damage_animation_finished");

		Ref<PackedScene> sound = ResourceLoader::get_singleton()->load(ResourceContainer::_get_instance()->target_hit());
		get_parent()->add_child(sound->instance());
	}

	if (_hp <= 0)
	{
		Enemies::get_singleton()->_set_enemy_count(0);
		CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->call("_open_doors");

		auto cur_room = CurrentRoom::get_singleton()->_get_current_room();
		for (int i = cur_room->get_child_count() - 1; i >= 0; --i)
			if (cur_room->get_child(i)->get_name().find("fill_door") != -1)
				cast_to<Node2D>(cur_room->get_child(i))->hide();

		auto player = player_id == 1 ? PlayersContainer::_get_instance()->_get_player1()
			: PlayersContainer::_get_instance()->_get_player2_regular();

		if (player != nullptr)
		{
			if (player->get_global_position().x <= get_global_position().x)
			{
				sprite->play("fall");
				Ref<PackedScene> sound = ResourceLoader::get_singleton()->load(ResourceContainer::_get_instance()->target_hit());
				get_parent()->add_child(sound->instance());
			}
			else
			{
				sprite->play("crack");
				Ref<PackedScene> sound = ResourceLoader::get_singleton()->load(ResourceContainer::_get_instance()->target_crack());
				get_parent()->add_child(sound->instance());
			}
		}

		health_bar->set_visible(false);
		cast_to<Area2D>(get_node("Area2D"))->set_collision_layer_bit(0, false);
		cast_to<Area2D>(get_node("Area2D"))->set_collision_mask_bit(0, false);
		this->set_collision_mask_bit(9, false);
		this->set_collision_layer_bit(2, false);
	}

}

void godot::TutorialEnemy::_on_damage_animation_finished()
{
	sprite->disconnect("animation_finished", this, "_on_damage_animation_finished");
	sprite->play("idle");
}

void godot::TutorialEnemy::_on_spawn_end()
{
	timer->disconnect("timeout", this, "_on_spawn_end");
	health_bar->set_visible(true);
	sprite->set_visible(true);
	cast_to<Particles2D>(get_node("SpawnParticles"))->set_emitting(false);
}

godot::TutorialEnemy::TutorialEnemy()
{
	_hp = 100;
	sprite = nullptr;
	health_bar = nullptr;
	timer = Timer::_new();
}

godot::TutorialEnemy::~TutorialEnemy()
{
	sprite = nullptr;
	health_bar = nullptr;
	timer = nullptr;
}
