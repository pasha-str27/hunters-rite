#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::BigStone::_register_methods()
{
	register_method("_init", &BigStone::_init);
	register_method("_ready", &BigStone::_ready);
	register_method("_add_player", &BigStone::_add_player);
	register_method("_set_new_z_index_for_player", &BigStone::_set_new_z_index_for_player);
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
	timer = Timer::_new();
}

void godot::BigStone::_ready()
{
	add_child(timer);

	idle_particles = cast_to<Particles2D>(get_node("StoneIdleParticles"));
	sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
}

void godot::BigStone::_set_new_z_index_for_player(Node2D* node, int index)
{
	if (node->is_in_group("player"))
	{
		if (node->is_in_group("player1"))
		{
			cast_to<AnimatedSprite>(node->get_node("AnimatedSprite"))->set_z_index(index);
			return;
		}
		node->set_z_index(index);
	}
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

	if (can_heal)
		_heal_players();
}

bool godot::BigStone::player_is_ghost()
{
	auto player_container = PlayersContainer::_get_instance();

	bool check_res = false;

	auto _try_heal = [](Node2D* player) -> bool {
		bool check_res = false;
		if (player != nullptr)
		{
			if (player->has_method("_is_ghost_mode"))
				check_res = (bool)player->call("_is_ghost_mode");
			else
			{
				for (int i = 0; i < player->get_child_count(); ++i)
					if (player->get_child(i)->has_method("_is_ghost_mode"))
						check_res = (bool)player->get_child(i)->call("_is_ghost_mode");
			}
		}
		return check_res;
	};

	auto player1 = player_container->_get_player1_regular();
	check_res = _try_heal(player1);

	auto player2 = player_container->_get_player2_regular();
	check_res = _try_heal(player2);

	return check_res;
}

void godot::BigStone::_change_player_moving(Node2D* player, bool value)
{
	if (player == nullptr)
		return;

	if (player->has_method("_change_moving"))
	{
		player->call_deferred("_change_moving", value);
		return;
	}

	for (int i = 0; i < player->get_child_count(); ++i)
		if (player->get_child(i)->has_method("_change_moving"))
		{
			player->get_child(i)->call_deferred("_change_moving", value);
			break;
		}
}

void godot::BigStone::_make_sound()
{
	Ref<PackedScene> prefab = nullptr;
	prefab = ResourceLoader::get_singleton()->load(ResourceContainer::_get_instance()->stone_action());
	get_parent()->add_child(prefab->instance());
}

void godot::BigStone::_spawn_particles()
{
	auto particles = cast_to<Node2D>(use_particles->instance());
	particles->set_global_position(this->get_global_position());
	get_node("/root/Node2D/Node")->add_child(particles);
}

godot::BigStone::BigStone()
{
}

godot::BigStone::~BigStone()
{
	timer = nullptr;
	sprite = nullptr;
	idle_particles = nullptr;
}

void godot::BigStone::_heal_players()
{
	auto player_container = PlayersContainer::_get_instance();

	auto player1 = player_container->_get_player1_regular();
	auto player2 = player_container->_get_player2_regular();

	if (MenuButtons::game_mode == COOP && players_count == 2)
	{
		sprite->set_speed_scale(2);
		sprite->play("light");

		sprite->connect("animation_finished", this, "_start_hide_animation");

		if (player1 != nullptr)
		{
			_heal_player(player1);
			_change_player_moving(player1, false);
		}

		if (player2 != nullptr)
		{
			_change_player_moving(player2, false);

			if (player2->has_method("_heal"))
				_heal_player(player2);
		}

		can_heal = false;

		if (!player_is_ghost())
		{
			timer->connect("timeout", this, "_can_heal_true");
			timer->start(heal_cooldown);
		}
	}

	if ((MenuButtons::game_mode == SHOOTER || MenuButtons::game_mode == MELEE) && players_count == 1)
	{
		sprite->set_speed_scale(2);
		sprite->play("light");

		sprite->connect("animation_finished", this, "_start_hide_animation");

		if (player1 != nullptr)
		{
			_heal_player(player1);
			_change_player_moving(player1, false);
		}

		if (player2 != nullptr)
		{
			_heal_player(player2);
			_change_player_moving(player2, false);
		}

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

	_make_sound();

	_spawn_particles();

	sprite->set_speed_scale(1);
	sprite->play("hide");

	idle_particles->set_emitting(false);

	auto player_container = PlayersContainer::_get_instance();
	auto player1 = player_container->_get_player1_regular();
	auto player2 = player_container->_get_player2_regular();

	if (player1 != nullptr)
		_change_player_moving(player1, true);

	if (player2 != nullptr)
		_change_player_moving(player2, true);
}

void godot::BigStone::_can_heal_true()
{
	if (timer->is_connected("timeout", this, "_can_heal_true"))
		timer->disconnect("timeout", this, "_can_heal_true");

	can_heal = true;
	sprite->set_speed_scale(1);
	sprite->play("idle");
	idle_particles->set_emitting(true);
	_heal_players();
}
