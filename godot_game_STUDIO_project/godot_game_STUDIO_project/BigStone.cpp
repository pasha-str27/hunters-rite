#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::BigStone::_register_methods()
{
	register_method("_init", &BigStone::_init);
	register_method("_ready", &BigStone::_ready);
	register_method("_add_player", &BigStone::_add_player);
	register_method("_remove_player", &BigStone::_remove_player);
	register_method("_can_heal_true", &BigStone::_can_heal_true);
	register_method("_change_start_parameters", &BigStone::_change_start_parameters);
	register_method("_start_hide_animation", &BigStone::_start_hide_animation);
	

	register_property<BigStone, Ref<PackedScene>>("particles for use", &BigStone::use_particles, nullptr);
}

void godot::BigStone::_init()
{
	can_heal = true;
	heal_cooldown = 30;
}

void godot::BigStone::_ready()
{
	timer = Timer::_new();
	add_child(timer);

	idle_particles = cast_to<Particles2D>(get_node("StoneIdleParticles"));
	sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
}


void godot::BigStone::_remove_player(Node2D* node)
{
	if (node->is_in_group("player"))
		--players_count;
}

void godot::BigStone::_add_player(Node2D* node)
{
	if (node->is_in_group("player"))
		++players_count;

	if(can_heal)
		_heal_players();
}

void godot::BigStone::_heal_players()
{
	auto player_conteiner = PlayersContainer::_get_instance();

	if (MenuButtons::game_mode == COOP && players_count == 2)
	{
		sprite->set_speed_scale(2);
		sprite->play("light");

		sprite->connect("animation_finished", this, "_start_hide_animation");

		if (player_conteiner->_get_player1_regular() != nullptr)
			_heal_player(player_conteiner->_get_player1_regular());
		if (player_conteiner->_get_player2_regular()->has_method("_heal"))
			_heal_player(player_conteiner->_get_player2_regular());
		
		Ref<PackedScene> prefab = nullptr;
		prefab = ResourceLoader::get_singleton()->load(ResourceContainer::_get_instance()->stone_action());
		get_parent()->add_child(prefab->instance());

		can_heal = false;
		timer->connect("timeout", this, "_can_heal_true");
		timer->start(heal_cooldown);

	}

	if ((MenuButtons::game_mode == SHOOTER || MenuButtons::game_mode == MELEE) && players_count == 1)
	{
		sprite->set_speed_scale(2);
		sprite->play("light");

		sprite->connect("animation_finished", this, "_start_hide_animation");

		if (player_conteiner->_get_player1_regular() != nullptr)
			_heal_player(player_conteiner->_get_player1_regular());

		if (player_conteiner->_get_player2_regular() != nullptr)
			_heal_player(player_conteiner->_get_player2_regular());
		
		can_heal = false;
		timer->connect("timeout", this, "_can_heal_true");
		timer->start(heal_cooldown);

	}
}

void godot::BigStone::_heal_player(Node2D* player)
{
	if (player->has_method("_heal"))
	{
		player->call_deferred("_heal");
		return;
	}

	for (int i = 0; i < player->get_child_count(); ++i)
		if (player->get_child(i)->has_method("_heal"))
		{
			player->get_child(i)->call_deferred("_heal");
			return;
		}
}

void godot::BigStone::_change_start_parameters()
{
	Vector2 cur_pos = (get_global_position() - cast_to<Node2D>(get_parent())->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
	get_parent()->call("_set_cell_value", cur_pos.y, cur_pos.x, 7);

	get_parent()->call("_set_cell_value", cur_pos.y + 1, cur_pos.x, 7);
	get_parent()->call("_set_cell_value", cur_pos.y, cur_pos.x + 1, 7);
	get_parent()->call("_set_cell_value", cur_pos.y + 1, cur_pos.x + 1, 7);
	get_parent()->call("_set_cell_value", cur_pos.y - 1, cur_pos.x, 7);
	get_parent()->call("_set_cell_value", cur_pos.y, cur_pos.x - 1, 7);
	get_parent()->call("_set_cell_value", cur_pos.y - 1, cur_pos.x - 1, 7);
	get_parent()->call("_set_cell_value", cur_pos.y - 1, cur_pos.x + 1, 7);
	get_parent()->call("_set_cell_value", cur_pos.y + 1, cur_pos.x - 1, 7);
}

void godot::BigStone::_start_hide_animation()
{
	sprite->disconnect("animation_finished", this, "_start_hide_animation");

	auto particles = cast_to<Node2D>(use_particles->instance());
	particles->set_global_position(this->get_global_position());
	get_node("/root/Node2D/Node")->add_child(particles);

	sprite->set_speed_scale(1);
	sprite->play("hide");

	idle_particles->set_emitting(false);
}

void godot::BigStone::_can_heal_true()
{
	timer->disconnect("timeout", this, "_can_heal_true");
	can_heal = true;
	sprite->set_speed_scale(1);
	sprite->play("idle");
	idle_particles->set_emitting(true);
	_heal_players();
}
