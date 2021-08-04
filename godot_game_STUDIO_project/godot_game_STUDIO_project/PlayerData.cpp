#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::Input* godot::PlayerData::input_controller = nullptr;

godot::PlayerData::PlayerData(Node2D* object, Ref<PackedScene> bullet)
{
	input_map["move_up"] = "Player_up";
	input_map["move_down"] = "Player_down";
	input_map["move_left"] = "Player_left";
	input_map["move_right"] = "Player_right";
	input_map["fight_up"] = "Player_fight_up";
	input_map["fight_down"] = "Player_fight_down";
	input_map["fight_left"] = "Player_fight_left";
	input_map["fight_right"] = "Player_fight_right";
	input_map["special"] = "Player_special";

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
	cast_to<KinematicBody2D>(object)->move_and_slide(dir.normalized() * speed);
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

void godot::PlayerData::_set_right_HP(float HP)
{
	this->HP = HP;
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

ProgressBar* godot::PlayerData::_get_health_bar()
{
	return nullptr;
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

void godot::PlayerData::_set_controll_buttons(Dictionary input_map)
{
	this->input_map = input_map;
	//this->input_map["move_up"] = ((String)input_map["move_up"]).;
	//this->input_map["move_down"] = (String)input_map["move_down"];
	//this->input_map["move_left"] = (String)input_map["move_left"];
	//this->input_map["move_right"] = (String)input_map["move_right"];
	//this->input_map["fight_up"] = (String)input_map["fight_up"];
	//this->input_map["fight_down"] = (String)input_map["fight_down"];
	//this->input_map["fight_left"] = (String)input_map["fight_left"];
	//this->input_map["fight_right"] = (String)input_map["fight_right"];
	//this->input_map["special"] = (String)input_map["special"];
}

Dictionary godot::PlayerData::_get_controll_buttons()
{
	return input_map;
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

void godot::PlayerData::_decrease_attack_radius()
{
}

void godot::PlayerData::_encrease_attack_radius()
{
}
