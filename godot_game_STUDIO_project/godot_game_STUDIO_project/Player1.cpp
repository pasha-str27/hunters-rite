#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Player1* godot::Player1::singleton = nullptr;

godot::Player1::Player1(Node2D* object, Ref<PackedScene>bullet) : PlayerData(object)
{
	max_bullet_count = 30;

	auto node = get_object()->get_node("/root/Node2D/BulletConteiner");

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

void godot::Player1::move()
{
	PlayerData::move();
}

void godot::Player1::process_input()
{
	Vector2 dir = Vector2(0, 0);

	//fight	up
	if (input_controller->is_action_pressed("Player1_fight_up"))
	{
		bullet_dir = Vector2::UP;
		fight();
	}

	//fight	down
	if (input_controller->is_action_pressed("Player1_fight_down"))
	{
		bullet_dir = Vector2::DOWN;
		fight();
	}

	//fight	left
	if (input_controller->is_action_pressed("Player1_fight_left"))
	{
		bullet_dir = Vector2::LEFT;
		fight();
	}

	//fight	right
	if (input_controller->is_action_pressed("Player1_fight_right"))
	{
		bullet_dir = Vector2::RIGHT;
		fight();
	}

	//move up
	if (input_controller->is_action_pressed("Player1_up"))
	{
		dir.y -= get_speed();
	}

	//move down
	if (input_controller->is_action_pressed("Player1_down"))
	{
		dir.y += get_speed();
	}

	//move left
	if (input_controller->is_action_pressed("Player1_left"))
	{
		cast_to<Sprite>(get_object()->get_child(0)->get_child(0))->set_flip_h(false);
		dir.x -= get_speed();
	}

	//move right	
	if (input_controller->is_action_pressed("Player1_right"))
	{
		cast_to<Sprite>(get_object()->get_child(0)->get_child(0))->set_flip_h(true);
		dir.x += get_speed();
	}

	PlayerData::set_dir(dir);
}

void godot::Player1::fight()	
{
	available_bullets[available_bullets.size() - 1]->set_position(get_object()->get_global_position());
	available_bullets[available_bullets.size() - 1]->set_visible(true);

	if ((bullet_dir + get_dir()).normalized() == godot::Vector2::ZERO)
		available_bullets[available_bullets.size() - 1]->call("set_dir", (bullet_dir).normalized());
	else
		available_bullets[available_bullets.size() - 1]->call("set_dir", (bullet_dir + get_dir()).normalized());

	if (available_bullets.size() == 1)
	{
		auto node = get_object()->get_node("/root/Node2D/BulletConteiner");
		auto new_obj = available_bullets[0]->duplicate(8);
		node->add_child(new_obj);
		available_bullets.push_back(cast_to<Node2D>(new_obj));
	}

	available_bullets.pop_back();
}

void godot::Player1::set_speed(float speed)
{
	PlayerData::set_speed(speed);
}

void godot::Player1::add_bullet(Node* node)
{
	cast_to<Node2D>(node)->set_visible(false);
	available_bullets.push_back(cast_to<Node2D>(node));
}

