#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Player2* godot::Player2::singleton = nullptr;

godot::Player2::Player2(Node2D* obj, Ref<PackedScene> bullet) : PlayerData(obj)
{
	_change_can_fight(true);
	current_enemy = nullptr;
}

godot::Player2::~Player2()
{
}

void godot::Player2::_move()
{
	PlayerData::_move();
}

void godot::Player2::_process_input()
{
	Vector2 dir = Vector2(0, 0);

	//move up
	if (input_controller->is_action_just_pressed("Player2_fight"))
	{
		_fight();
	}

	//move up
	if (input_controller->is_action_pressed("Player2_up"))
	{
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(90);
		dir.y -= _get_speed();
	}

	//move down
	if (input_controller->is_action_pressed("Player2_down"))
	{
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(270);
		dir.y += _get_speed();
	}

	//move left
	if (input_controller->is_action_pressed("Player2_left"))
	{
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(0);
		cast_to<Sprite>(_get_object()->get_child(0)->get_child(0))->set_flip_h(false);
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed("Player2_right"))
	{
		cast_to<Node2D>(_get_object()->get_child(1))->set_rotation_degrees(180);
		cast_to<Sprite>(_get_object()->get_child(0)->get_child(0))->set_flip_h(true);
		dir.x += _get_speed();
	}

	PlayerData::_set_dir(dir);
}

void godot::Player2::_fight(Node* node)
{
	if (!_can_fight())
		return;

	_change_can_fight(false);

	if (current_enemy)
	{
		current_enemy->call("_take_damage", 25);
	}

	cast_to<Node2D>(_get_object()->get_child(1))->set_visible(true);
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
	PlayerData::_take_damage(damage, is_spike);

	if (_get_HP() <= 0)
	{
		_get_object()->queue_free();
		Enemies::get_singleton()->_remove_player2();
	}
}