#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::TutorialEnemy::_register_methods()
{
	register_method("_ready", &TutorialEnemy::_ready);
	register_method("_take_damage", &TutorialEnemy::_take_damage);
	register_method("_on_damage_animation_finished", &TutorialEnemy::_on_damage_animation_finished);

	register_property<TutorialEnemy, float>("HP", &TutorialEnemy::_hp, 100);
}

void godot::TutorialEnemy::_init()
{
}

void godot::TutorialEnemy::_ready()
{
	sprite = cast_to<AnimatedSprite>(find_node("Sprite"));
	health_bar = cast_to<ProgressBar>(get_node("HealthBar"));


	//	set healthbar values
	health_bar->set_visible(true);
	health_bar->set_max(_hp);
	health_bar->set_value(_hp);

	cast_to<Area2D>(get_node("Area2D"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(get_node("Area2D"))->set_collision_mask_bit(0, true);
	this->set_collision_mask_bit(9, true);
	this->set_collision_layer_bit(2, true);
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
	}

	if (_hp <= 0)
	{
		auto player = player_id == 1 ? PlayersContainer::_get_instance()->_get_player1()
			: PlayersContainer::_get_instance()->_get_player2_regular();

		if (player != nullptr)
		{
			if(player->get_global_position().x <= get_global_position().x)
				sprite->play("fall");
			else
				sprite->play("crack");
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

godot::TutorialEnemy::TutorialEnemy()
{
	_hp = 100;
	sprite = nullptr;
	health_bar = nullptr;
}

godot::TutorialEnemy::~TutorialEnemy()
{
	sprite = nullptr;
	health_bar = nullptr;
}
