#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Player1* godot::Player1::singleton = nullptr;

godot::Player1::Player1(Node2D* object, Ref<PackedScene>bullet) : PlayerData(object)
{
	max_bullet_count = 30;
	_change_can_fight(true);

	auto node = _get_object()->get_node("/root/Node2D/BulletConteiner");

	for (int i = 0; i < max_bullet_count; ++i)
	{
		auto new_obj = bullet->instance();
		node->add_child(new_obj);
		available_bullets.push_back(cast_to<Node2D>(new_obj));
	}
}

godot::Player1::~Player1()
{
	available_bullets.clear();
}

void godot::Player1::_move()
{
	PlayerData::_move();
}

void godot::Player1::_process_input()
{
	Vector2 dir = Vector2(0, 0);

	if (input_controller->is_action_just_pressed("Player1_left"))
	{
		cast_to<Sprite>(_get_object()->get_child(0)->get_child(0))->set_flip_h(false);
	}

	if (input_controller->is_action_just_pressed("Player1_right"))
	{
		cast_to<Sprite>(_get_object()->get_child(0)->get_child(0))->set_flip_h(true);
	}

	//move up
	if (input_controller->is_action_pressed("Player1_up"))
	{
		dir.y -= _get_speed();
	}

	//move down
	if (input_controller->is_action_pressed("Player1_down"))
	{
		dir.y += _get_speed();
	}

	//move left
	if (input_controller->is_action_pressed("Player1_left"))
	{
		dir.x -= _get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed("Player1_right"))
	{
		dir.x += _get_speed();
	}

	//fight	up
	if (input_controller->is_action_pressed("Player1_fight_up"))
	{
		bullet_dir = Vector2::UP;
		_fight();
	}

	//fight	down
	if (input_controller->is_action_pressed("Player1_fight_down"))
	{
		bullet_dir = Vector2::DOWN;
		_fight();
	}

	//fight	left
	if (input_controller->is_action_pressed("Player1_fight_left"))
	{
		bullet_dir = Vector2::LEFT;
		cast_to<Sprite>(_get_object()->get_child(0)->get_child(0))->set_flip_h(false);
		_fight();
	}

	//fight	right
	if (input_controller->is_action_pressed("Player1_fight_right"))
	{
		bullet_dir = Vector2::RIGHT;
		cast_to<Sprite>(_get_object()->get_child(0)->get_child(0))->set_flip_h(true);
		_fight();
	}

	PlayerData::_set_dir(dir);
}

void godot::Player1::_fight(Node* node)
{
	if (!_can_fight())
		return;

	_change_can_fight(false);

	available_bullets[available_bullets.size() - 1]->set_position(_get_object()->get_global_position());
	available_bullets[available_bullets.size() - 1]->set_visible(true);

	if ((bullet_dir + _get_dir()).normalized() == godot::Vector2::ZERO)
		available_bullets[available_bullets.size() - 1]->call("_set_dir", (bullet_dir).normalized());
	else
		available_bullets[available_bullets.size() - 1]->call("_set_dir", (bullet_dir + _get_dir()).normalized());

	if (available_bullets.size() == 1)
	{
		auto node = _get_object()->get_node("/root/Node2D/BulletConteiner");
		auto new_obj = available_bullets[0]->duplicate(8);
		node->add_child(new_obj);
		available_bullets.push_back(cast_to<Node2D>(new_obj));
	}

	available_bullets.pop_back();

	_get_object()->call("_start_timer");
}

void godot::Player1::_set_speed(float speed)
{
	PlayerData::_set_speed(speed);
}

void godot::Player1::_set_enemy(Node* enemy)
{
}

void godot::Player1::_add_bullet(Node* node)
{
	cast_to<Node2D>(node)->set_visible(false);
	available_bullets.push_back(cast_to<Node2D>(node));
}
