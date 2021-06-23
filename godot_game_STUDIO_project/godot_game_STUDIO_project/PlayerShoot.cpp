#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::PlayerShoot::PlayerShoot(Node2D* object, Ref<PackedScene> bullet) : PlayerData(object)
{
	max_bullet_count = 10;
	_change_can_fight(true);

	auto node = _get_object()->get_parent()->get_child(0);
	
	sprite = cast_to<AnimatedSprite>(_get_object()->get_node("AnimatedSprite"));

	shoot_particles = cast_to<Particles2D>(sprite->get_child(0));

	if (node->get_child_count() == 0)
	{
		for (int i = 0; i < max_bullet_count; ++i)
		{
			auto new_obj = bullet->instance();
			node->add_child(new_obj);
			available_bullets.push_back(cast_to<Node2D>(new_obj));
		}
	}
	else
		for (int i = 0; i < node->get_child_count(); ++i)
			available_bullets.push_back(cast_to<Node2D>(node->get_child(i)));

	sprite->play("idle");
	_set_special_time(0.5);

	cast_to<KinematicBody2D>(object)->set_collision_mask_bit(1, true);
	cast_to<KinematicBody2D>(object)->set_collision_layer_bit(0, true);
	cast_to<KinematicBody2D>(object)->set_collision_layer_bit(15, true);
	cast_to<Area2D>(object->get_node("Area2D"))->set_collision_mask_bit(0, true);
	cast_to<Area2D>(object->get_node("Area2D"))->set_collision_layer_bit(0, true);
}

godot::PlayerShoot::~PlayerShoot()
{
	sprite = nullptr;
	shoot_particles = nullptr;
	available_bullets.clear();
}

void godot::PlayerShoot::_set_HP(float value)
{
	PlayerData::_set_HP(value);

	if (_get_HP() <= 0)
	{
		Enemies::get_singleton()->_remove_player1();

		if (_was_revived())
		{
			_get_object()->get_parent()->queue_free();
			return;
		}

		_get_object()->call("_die");
	}
}

void godot::PlayerShoot::_move()
{
	PlayerData::_move();

	String animation_name = sprite->get_animation();
	if (sprite->get_sprite_frames()->get_animation_loop(animation_name) == false && sprite->get_frame() == sprite->get_sprite_frames()->get_frame_count(animation_name) - 1)
		sprite->play("idle");

	if (PlayerData::_get_dir() == Vector2::ZERO && animation_name != "revive" && animation_name != "damaged")
		sprite->play("idle");

	if (PlayerData::_get_dir() != Vector2::ZERO && sprite->get_animation() == "idle")
		sprite->play("run");
}

void godot::PlayerShoot::_process_input()
{
	Vector2 dir = Vector2(0, 0);

	//fight	up
	if (input_controller->is_action_pressed(fight_up))
	{
		shoot_particles->set_position(Vector2(0, -9));
		bullet_dir = Vector2::UP;
		_fight();
	}

	//fight	down
	if (input_controller->is_action_pressed(fight_down))
	{
		shoot_particles->set_position(Vector2(0, 9));
		bullet_dir = Vector2::DOWN;
		_fight();
	}

	//fight	left
	if (input_controller->is_action_pressed(fight_left))
	{
		bullet_dir = Vector2::LEFT;
		sprite->set_flip_h(true);
		sprite->set_offset(Vector2(-35, 0));
		shoot_particles->set_position(Vector2(-11, 0));
		_fight();
	}

	//fight	right
	if (input_controller->is_action_pressed(fight_right))
	{
		bullet_dir = Vector2::RIGHT;
		sprite->set_flip_h(false);
		sprite->set_offset(Vector2(35, 0));
		shoot_particles->set_position(Vector2(11, 0));
		_fight();
	}

	//move up
	if (input_controller->is_action_pressed(move_up))
		dir.y -= _get_speed();

	//move down
	if (input_controller->is_action_pressed(move_down))
		dir.y += _get_speed();

	//move left
	if (input_controller->is_action_pressed(move_left))
	{
		sprite->set_flip_h(true);
		sprite->set_offset(Vector2(-35, 0));
		shoot_particles->set_position(Vector2(-11, 0));
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed(move_right))
	{
		sprite->set_flip_h(false);
		sprite->set_offset(Vector2(35, 0));
		shoot_particles->set_position(Vector2(11, 0));
		dir.x += _get_speed();
	}

	//dash
	if (input_controller->is_action_just_pressed(special))
		_get_object()->call("_start_special_timer");

	PlayerData::_set_dir(dir);
}

void godot::PlayerShoot::_fight(Node* node)
{
	if (!_can_fight())
		return;

	Ref<PackedScene> prefab = nullptr;
	prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/SoundsEffects/Effects/Player1Fight.tscn");
	_get_object()->add_child(prefab->instance());

	_change_can_fight(false);

	available_bullets[available_bullets.size() - 1]->set_position(_get_object()->get_global_position());
	available_bullets[available_bullets.size() - 1]->set_visible(true);


	if ((bullet_dir + _get_dir()).normalized() == godot::Vector2::ZERO)
		available_bullets[available_bullets.size() - 1]->call("_set_dir", (bullet_dir).normalized());
	else
		available_bullets[available_bullets.size() - 1]->call("_set_dir", (bullet_dir + _get_dir()).normalized());

	if (available_bullets.size() == 1)
	{
		auto node = _get_object()->get_parent()->get_child(0);
		auto new_obj = available_bullets[0]->duplicate(8);
		node->add_child(new_obj);
		available_bullets.push_back(cast_to<Node2D>(new_obj));
	}

	available_bullets[available_bullets.size() - 1]->call("_set_damage", _get_damage());

	available_bullets.pop_back();

	shoot_particles->restart();

	_get_object()->call("_start_timer");
}

void godot::PlayerShoot::_add_bullet(Node* node)
{
	available_bullets.push_back(cast_to<Node2D>(node));
}

void  godot::PlayerShoot::_take_damage(float damage, bool is_spike)
{
	if (_get_HP() <= 0)
		return;

	PlayerData::_take_damage(damage, is_spike);

	sprite->play("damaged");

	if (_get_HP() <= 0)
	{
		Ref<PackedScene> prefab = nullptr;
		prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/SoundsEffects/Effects/PlayerDied.tscn");
		_get_object()->get_parent()->add_child(prefab->instance());

		sprite->play("death");
		PlayersContainer::_get_instance()->_set_player1(nullptr);
		Enemies::get_singleton()->_remove_player1();

		_get_object()->call("_die");
	}
}

void godot::PlayerShoot::_update_health_bar()
{
	auto health_bar = _get_health_bar();
	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::PlayerShoot::_get_health_bar()
{
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P1HealthBarWrapper/ProgressBar"));
}

void godot::PlayerShoot::_stop_animations()
{
	sprite->play("idle");
	_set_dir(Vector2::ZERO);
}

void godot::PlayerShoot::_stop_special()
{
	_set_speed(_get_speed() / speed_delta);
}

void godot::PlayerShoot::_start_special()
{
	_set_speed(_get_speed() * speed_delta);
}

void godot::PlayerShoot::_set_controll_buttons(String move_up, String move_down, String move_left, String move_right, String fight_up, String fight_down, String fight_left, String fight_right, String special)
{
	PlayerData::_set_controll_buttons(move_up, move_down, move_left, move_right, fight_up, fight_down, fight_left, fight_right, special);
}
