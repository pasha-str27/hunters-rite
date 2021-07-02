#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Input* godot::PlayerData::input_controller = nullptr;

godot::PlayerData::PlayerData(Node2D* object, Ref<PackedScene> bullet)
{
	this->object = object;
	dir = Vector2(0, 0);
	HP = 0;
	max_HP = 0;
	damage = 25;
	was_revived = false;
	can_fight_value = true;
	speed = 250;

	if(input_controller == nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::PlayerData()
{
	object = nullptr;
	HP = 0;
	dir = Vector2(0, 0);
	was_revived = false;
	max_HP = 0;
	damage = 25;
	speed = 250;
	can_fight_value = true;

	if (input_controller == nullptr)
		input_controller = Input::get_singleton();
}

godot::PlayerData::~PlayerData()
{
	object = nullptr;
}

void godot::PlayerData::_move()
{
	cast_to<KinematicBody2D>(object)->move_and_slide(dir.normalized()*speed);
}

void godot::PlayerData::_set_speed(float speed)
{
	this->speed = speed > 0 ? speed : 0;
}

void godot::PlayerData::_fight(Node* node)
{
}

void godot::PlayerData::_add_bullet(Node* node)
{
}

float godot::PlayerData::_get_speed()
{
	return speed;
}

void godot::PlayerData::_set_dir(Vector2 dir)
{
	this->dir = dir;
}

godot::Vector2 godot::PlayerData::_get_dir()
{
	return dir.normalized();
}

godot::Node2D* godot::PlayerData::_get_object()
{
	return object;
}

void godot::PlayerData::_take_damage(float damage, bool is_spike)
{
	HP = (HP - damage > 0) ? HP - damage : 0;

	if(is_spike)
		object->set_global_position(object->get_global_position() - dir.normalized() * damage*2);
}

void godot::PlayerData::_change_can_fight(bool value)
{
	can_fight_value = value;
}

bool godot::PlayerData::_can_fight()
{
	return can_fight_value;
}

void godot::PlayerData::_process_input()
{
}

void godot::PlayerData::_set_enemy(Node* enemy)
{
}

float godot::PlayerData::_get_HP()
{
	return HP;
}

void godot::PlayerData::_set_HP(float HP)
{
	this->HP = HP > 0 ? HP : 10;
	this->HP = HP > max_HP ? max_HP : this->HP;
}

float godot::PlayerData::_get_damage()
{
	return damage;
}

void godot::PlayerData::_set_damage(float value)
{
	damage = value > 0 ? value : 0;
}

void godot::PlayerData::_revive()
{
	was_revived = true;
}

bool godot::PlayerData::_was_revived()
{
	return was_revived;
}

void godot::PlayerData::_set_was_revived(bool value)
{
	was_revived = value;
}

float godot::PlayerData::_get_max_HP()
{
	return max_HP;
}

void godot::PlayerData::_set_max_HP(float value)
{
	float diff = value - max_HP;
	max_HP = value;
	float _hp = this->HP + diff;
	_set_HP(_hp);
}

void godot::PlayerData::_stop_animations()
{
}

float godot::PlayerData::_get_special_time()
{
	return special_time;
}

void godot::PlayerData::_set_special_time(float value)
{
	special_time = value;
}

void godot::PlayerData::_set_safe_mode(bool value)
{
	is_safe_mode = value;
}

bool godot::PlayerData::_get_safe_mode()
{
	return is_safe_mode;
}

void godot::PlayerData::_stop_special()
{
}

void godot::PlayerData::_start_special()
{
}

void godot::PlayerData::_set_controll_buttons(String move_up, String move_down, String move_left, String move_right, String fight_up, String fight_down, String fight_left, String fight_right, String special)
{
	this->move_up = move_up;
	this->move_down = move_down;
	this->move_left = move_left;
	this->move_right = move_right;
	this->fight_up = fight_up;
	this->fight_down = fight_down;
	this->fight_left = fight_left;
	this->fight_right = fight_right;
	this->special = special;
}

std::map<String, String> godot::PlayerData::_get_controll_buttons()
{
	std::map<String, String> controlls;
	controlls.insert(std::make_pair("move_up", move_up));
	controlls.insert(std::make_pair("move_down", move_down));
	controlls.insert(std::make_pair("move_left", move_left));
	controlls.insert(std::make_pair("move_right", move_right));
	controlls.insert(std::make_pair("fight_up", fight_up));
	controlls.insert(std::make_pair("fight_down", fight_down));
	controlls.insert(std::make_pair("fight_left", fight_left));
	controlls.insert(std::make_pair("fight_right", fight_right));
	controlls.insert(std::make_pair("special", special));
	return controlls;
}

IPlayer* godot::PlayerData::_clone()
{
	return this;
}

void godot::PlayerData::_heal()
{
	_set_HP(_get_max_HP());
}

void godot::PlayerData::_set_is_attacking(bool value)
{
}
