#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Player2::Player2(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
	_change_can_fight(true);
	current_enemy = nullptr;
	sprite = cast_to<AnimatedSprite>(obj->get_child(0)->get_child(0));
	sprite->play("idle");

	vfx_sprite = cast_to<AnimatedSprite>(obj->get_child(1)->get_child(1));

	animator = cast_to<AnimationPlayer>(_get_object()->get_node("AnimationPlayer"));
}

godot::Player2::~Player2()
{
}

void godot::Player2::_move()
{
	PlayerData::_move();

	String animation_name = sprite->get_animation();
	if (sprite->get_sprite_frames()->get_animation_loop(animation_name) == false 
		&& sprite->get_frame() == sprite->get_sprite_frames()->get_frame_count(animation_name) - 1) 
	{
		sprite->set_offset(Vector2::ZERO);
		sprite->play("idle");
	}

	if (PlayerData::_get_dir() == Vector2::ZERO && animation_name != "revive" 
		&& animation_name != "damaged" && animation_name != "attack")
			sprite->play("idle");

	if (PlayerData::_get_dir() != Vector2::ZERO && sprite->get_animation() == "idle")
		sprite->play("run");

	if (sprite->is_flipped_h() && sprite->get_animation() == "attack")
		sprite->set_offset(Vector2(-26, -4));
	else 
		if (!sprite->is_flipped_h() && sprite->get_animation() == "attack")
			sprite->set_offset(Vector2(26, -4));
}

void godot::Player2::_process_input()
{
	Vector2 dir = Vector2(0, 0);

	//dash
	if (input_controller->is_action_just_pressed("Player2_dash"))
		_get_object()->call("_start_dash_timer");

	//move up
	if (input_controller->is_action_pressed("Player2_up"))
		dir.y -= _get_speed();

	//move down
	if (input_controller->is_action_pressed("Player2_down"))
		dir.y += _get_speed();

	//move left
	if (input_controller->is_action_pressed("Player2_left"))
	{
		sprite->set_flip_h(true);
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed("Player2_right"))
	{
		sprite->set_flip_h(false);
		dir.x += _get_speed();
	}

	//fight	up
	if (input_controller->is_action_pressed("Player2_fight_up"))
	{
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(270);
		if(_can_fight())
			animator->play("attack");
	}

	//fight	down
	if (input_controller->is_action_pressed("Player2_fight_down"))
	{
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(90);
		if (_can_fight()) 
			animator->play("attack");
	}

	//fight	left
	if (input_controller->is_action_pressed("Player2_fight_left"))
	{
		sprite->set_flip_h(true);
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(180);
		if (_can_fight())
			animator->play("attack");
	}

	//fight	right
	if (input_controller->is_action_pressed("Player2_fight_right"))
	{
		sprite->set_flip_h(false);
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(0);
		if (_can_fight())
			animator->play("attack");
	}

	PlayerData::_set_dir(dir);
}

void godot::Player2::_fight(Node* node)
{
	if (!_can_fight())
		return;

	Ref<PackedScene> prefab = nullptr;
	prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/SoundsEffects/Effects/Player2Fight.tscn");
	_get_object()->add_child(prefab->instance());

	_change_can_fight(false);

	if (current_enemy)
	{
		Array args = {};
		args.push_back(_get_damage());
		args.push_back(2);
		current_enemy->call("_take_damage", args);
	}

	_get_object()->call("_start_timer");
}

void godot::Player2::_add_bullet(Node* node)
{
}

void godot::Player2::_set_enemy(Node* enemy)
{
	current_enemy = enemy;
}

void godot::Player2::_set_speed(float speed)
{
	PlayerData::_set_speed(speed);
}

void godot::Player2::_take_damage(float damage, bool is_spike)
{
	if (_get_HP() <= 0)
		return;

	sprite->play("damaged");

	PlayerData::_take_damage(damage, is_spike);

	if (_get_HP() <= 0)
	{
		Enemies::get_singleton()->_remove_player2();

		sprite->play("death");
		if (_was_revived())
		{
			_get_object()->queue_free();
			return;
		}

		_get_object()->call("_die");
	}
}

void godot::Player2::_set_HP(float value)
{
	PlayerData::_set_HP(value);

	if (_get_HP() <= 0)
	{
		Enemies::get_singleton()->_remove_player2();
		PlayersContainer::_get_instance()->_set_player2(nullptr);

		if (_was_revived())
		{
			_get_object()->queue_free();
			return;
		}
		
		_get_object()->call("_die");
	}
}

void godot::Player2::_revive()
{
	sprite->play("revive");

	PlayerData::_revive();
	PlayersContainer::_get_instance()->_set_player2(_get_object());
}

void godot::Player2::_update_health_bar()
{
	auto health_bar = _get_health_bar();

	if (health_bar != nullptr)
		health_bar->set_value(_get_HP());
}

ProgressBar* godot::Player2::_get_health_bar()
{
	return cast_to<ProgressBar>(_get_object()->get_node("/root/Node2D/Node/Camera2D/P2HealthBarWrapper/ProgressBar"));
}

void godot::Player2::_stop_animations()
{
	sprite->play("idle");
	sprite->set_offset(Vector2::ZERO);
	_set_dir(Vector2::ZERO);
	vfx_sprite->stop();
	vfx_sprite->set_frame(0);
}
