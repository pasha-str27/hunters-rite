#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::PlayerController::_register_methods()
{
	register_method("_process", &PlayerController::_process);
	register_method("_ready", &PlayerController::_ready);
	register_method("_add_bullet", &PlayerController::_add_bullet);
	register_method("_start_timer", &PlayerController::_start_timer);
	register_method("_on_timeout", &PlayerController::_on_timeout);
	register_method("_start_special_timer", &PlayerController::_start_special_timer);
	register_method("_on_special_timeout", &PlayerController::_on_special_timeout);
	register_method("_start_dash_cooldow_timer", &PlayerController::_start_dash_cooldow_timer);
	register_method("_on_dash_cooldown_timeout", &PlayerController::_on_dash_cooldown_timeout);
	register_method("_can_fight", &PlayerController::_can_fight);
	register_method("_set_enemy", &PlayerController::_set_enemy);
	register_method("_on_Area2D_body_entered", &PlayerController::_on_Area2D_body_entered);
	register_method("_on_Area2D_area_entered", &PlayerController::_on_Area2D_area_entered);
	register_method("_on_Area2D_area_exited", &PlayerController::_on_Area2D_area_exited);
	register_method("_take_damage", &PlayerController::_take_damage);
	register_method("_change_can_moving", &PlayerController::_change_can_moving);
	register_method("_change_moving", &PlayerController::_change_moving);	
	register_method("change_can_moving_timeout", &PlayerController::change_can_moving_timeout);
	register_method("_decrease_attack_radius", &PlayerController::_decrease_attack_radius);
	register_method("_encrease_attack_radius", &PlayerController::_encrease_attack_radius);
	register_method("_set_number_to_next_item", &PlayerController::_set_number_to_next_item);
	register_method("_get_number_to_next_item", &PlayerController::_get_number_to_next_item);
	register_method("_set_speed", &PlayerController::_set_speed);
	register_method("_get_speed", &PlayerController::_get_speed);
	register_method("_set_HP", &PlayerController::_set_HP);
	register_method("_get_HP", &PlayerController::_get_HP);
	register_method("_set_damage", &PlayerController::_set_damage);
	register_method("_get_damage", &PlayerController::_get_damage);
	register_method("_set_attack_speed_delta", &PlayerController::_set_attack_speed_delta);
	register_method("_get_attack_speed_delta", &PlayerController::_get_attack_speed_delta);
	register_method("_change_can_fight", &PlayerController::_change_can_fight);
	register_method("_die", &PlayerController::_die);
	register_method("_revive", &PlayerController::_revive);
	register_method("_set_max_HP", &PlayerController::_set_max_HP);
	register_method("_get_max_HP", &PlayerController::_get_max_HP);
	register_method("_on_enemy_die", &PlayerController::_on_enemy_die);
	register_method("_is_alive", &PlayerController::_is_alive);
	register_method("_start_item_particles", &PlayerController::_start_item_particles);
	register_method("_update_health_bar", &PlayerController::_update_health_bar);
	register_method("_update_max_health_bar_size", &PlayerController::_update_max_health_bar_size);
	register_method("_animate_spider_web", &PlayerController::_animate_spider_web);
	register_method("_stop_animations", &PlayerController::_stop_animations);
	register_method("_player_fight", &PlayerController::_player_fight);	
	register_method("_set_controll_buttons", &PlayerController::_set_controll_buttons);
	register_method("_stay_ghost", &PlayerController::_stay_ghost);
	register_method("_heal", &PlayerController::_heal);
	register_method("_ghost_to_player", &PlayerController::_ghost_to_player);
	
	register_property<PlayerController, float>("hp", &PlayerController::_hp, 0);
	register_property<PlayerController, float>("damage", &PlayerController::_damage, 0);
	register_property<PlayerController, float>("speed", &PlayerController::speed, 400);
	register_property<PlayerController, Ref<PackedScene>>("bullet_prefab", &PlayerController::bullet_prefab, nullptr);
	register_property<PlayerController, Ref<PackedScene>>("revive_zone", &PlayerController::revive_zone, nullptr);
	register_property<PlayerController, float>("dash_cooldown_delta", &PlayerController::dash_cooldown_delta, 0);
}

godot::PlayerController::PlayerController()
{
	current_player_strategy = new PlayerStrategyContext;
	//current_player = nullptr;
	timer = Timer::_new();
	attack_speed_delta = 0.5;
	dash_time_delta = 0.4;
	dash_speed_multiplier = 1.5;
	dash_cooldown_delta = dash_time_delta * 3;
	number_to_next_item = 15;
	can_move = true;
	is_alive = true;
	is_special = false;
	speed = 250;
	door = nullptr;
}

godot::PlayerController::~PlayerController()
{
	if(current_player_strategy != nullptr)
		delete current_player_strategy;
	delete player_producer;
	current_player_strategy = nullptr;
	door = nullptr;
	item_generator = nullptr;
	timer = nullptr;
	hurt_particles = nullptr;
	buff_debuff_particles = nullptr;
	dash_particles = nullptr;
	revive_particles = nullptr;
	//if(current_player)
	//	delete current_player;
}

void godot::PlayerController::_init()
{
}

void godot::PlayerController::_ready()
{
	player_producer = nullptr;

	if (is_in_group("player1"))
	{
		player_producer = new ProducePlayerShoot;
		PlayersContainer::_get_instance()->_set_player1(this);
	}

	if (is_in_group("player2"))
	{
		player_producer = new ProducePlayerMelee;
		PlayersContainer::_get_instance()->_set_player2(this);
	}

	current_player_strategy->_set_strategy(player_producer->_get_player(this, bullet_prefab));

	current_player_strategy->_set_speed(speed);
	current_player_strategy->_set_max_HP(_hp);
	current_player_strategy->_set_HP(_hp);
	current_player_strategy->_set_damage(_damage);

	_update_max_health_bar_size();

	item_generator = CustomExtensions::GetChildByName(this, "ItemGenerator")->call("_get_instance");

	buff_debuff_particles = cast_to<Particles2D>(CustomExtensions::GetChildByName(this, "BuffDebuffParticles"));
	hurt_particles = cast_to<Particles2D>(CustomExtensions::GetChildByName(this, "HurtParticles"));
	dash_particles = cast_to<Particles2D>(CustomExtensions::GetChildByName(this, "DashParticles"));
	revive_particles = cast_to<Particles2D>(CustomExtensions::GetChildByName(this, "ReviveParticles"));
}

void godot::PlayerController::_start_timer()
{
	timer->connect("timeout", this, "_on_timeout");

	if (!has_node(NodePath(timer->get_name())))
		add_child(timer);

	timer->set_wait_time(attack_speed_delta);
	timer->start();
}

void godot::PlayerController::_on_timeout()
{
	timer->disconnect("timeout", this, "_on_timeout");

	current_player_strategy->_change_can_fight(true);
}

void godot::PlayerController::_start_special_timer()
{
	if (!timer->is_connected("timeout", this, "_start_special_timer") && !is_special)
	{
		timer->connect("timeout", this, "_on_special_timeout");

		if (!has_node(NodePath(timer->get_name())))
			add_child(timer);

		current_player_strategy->_start_special();

		_change_is_dashing_state();

		timer->start(current_player_strategy->_get_special_time());

		if(is_in_group("player1"))
			dash_particles->restart();
	}
}

void godot::PlayerController::_on_special_timeout()
{
	current_player_strategy->_stop_special();

	if(is_in_group("player2"))
		cast_to<AnimationPlayer>(get_node("Shield")->find_node("AnimationPlayer"))->play("shield_end");

	timer->disconnect("timeout", this, "_on_special_timeout");
	_start_dash_cooldow_timer();
}

void godot::PlayerController::_start_dash_cooldow_timer()
{
	if (!timer->is_connected("timeout", this, "_on_dash_cooldown_timeout") && is_special)
	{
		timer->connect("timeout", this, "_on_dash_cooldown_timeout");

		if (!has_node(NodePath(timer->get_name())))
			add_child(timer);

		timer->start(dash_cooldown_delta);
	}
}

void godot::PlayerController::_on_dash_cooldown_timeout()
{
	if (is_special)
		is_special = false;

	timer->disconnect("timeout", this, "_on_dash_cooldown_timeout");
}

void godot::PlayerController::_change_is_dashing_state()
{
	is_special = !is_special;
}

bool godot::PlayerController::_can_fight()
{
	return current_player_strategy->_can_fight();
}

void godot::PlayerController::_change_can_fight(bool value)
{
	return current_player_strategy->_change_can_fight(value);
}

void godot::PlayerController::_set_enemy(Node* enemy)
{
	current_player_strategy->_set_enemy(enemy);
}

void godot::PlayerController::_add_bullet(Node* node)
{
	current_player_strategy->_add_bullet(node);
}

void godot::PlayerController::_process(float delta)
{
	if (can_move && is_alive || is_ghost_mode)
	{
		current_player_strategy->_process_input();
		current_player_strategy->_move();
	}
}

void godot::PlayerController::_take_damage(float damage, bool is_spike)
{
	if (current_player_strategy->_get_safe_mode())
		return;

	current_player_strategy->_take_damage(damage, is_spike);
	_update_health_bar();

	if (is_alive)
	{
		Ref<PackedScene> prefab = nullptr;
		prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/SoundsEffects/Effects/PlayerTakeDamage.tscn");
		add_child(prefab->instance());
		hurt_particles->restart();
	}
}

void godot::PlayerController::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("spike"))
		_take_damage(node->call("_get_damage"), true);
}

void godot::PlayerController::_on_Area2D_area_entered(Node* node)
{
	auto camera = CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D");

	if (node->is_in_group("door_zone") && (is_alive || is_ghost_mode))
	{
		camera->call("_door_collision", node->get_name());
		door = node;
	}

	if (node->is_in_group("tutor"))
		_show_tutorial_message(node);
}

void godot::PlayerController::_on_Area2D_area_exited(Node* node)
{
	auto camera = CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D");

	if (node->is_in_group("door_zone") && is_alive)
	{
		camera->call("_door_collision", "-" + node->get_name());
		door = nullptr;
	}

	if (node->is_in_group("tutor"))
		_hide_tutorial_message(node);
}

void godot::PlayerController::_change_can_moving(bool value)
{
	can_move = false;

	if (timer->is_connected("timeout", this, "change_can_moving_timeout"))
		timer->disconnect("timeout", this, "change_can_moving_timeout");

	timer->connect("timeout", this, "change_can_moving_timeout");

	if (!has_node(NodePath(timer->get_name())))
		add_child(timer);

	timer->start(1.5);
}

void godot::PlayerController::_change_moving(bool value)
{
	can_move = value;
	if (!value && is_alive)
		current_player_strategy->_stop_animations();
}

void godot::PlayerController::change_can_moving_timeout()
{
	timer->disconnect("timeout", this, "change_can_moving_timeout");

	can_move = true;
}

void godot::PlayerController::_decrease_attack_radius()
{
	auto node = cast_to<Node2D>(get_child(1));
	node->set_scale(Vector2(node->get_scale().x * (real_t)1.1111, 1));
}

void godot::PlayerController::_encrease_attack_radius()
{
	auto node = cast_to<Node2D>(get_child(1));
	node->set_scale(Vector2(node->get_scale().x * (real_t)0.9, 1));
}

void godot::PlayerController::_set_number_to_next_item(int value)
{
	number_to_next_item = value;
}

int godot::PlayerController::_get_number_to_next_item()
{
	return number_to_next_item;
}

void godot::PlayerController::_set_speed(float value)
{
	speed = value;
	current_player_strategy->_set_speed(speed);
}

float godot::PlayerController::_get_speed()
{
	return speed;
}

void godot::PlayerController::_set_HP(float value)
{
	current_player_strategy->_set_HP(value);
	_update_health_bar();
}

float godot::PlayerController::_get_HP()
{
	return current_player_strategy->_get_HP();
}

void godot::PlayerController::_heal()
{
	current_player_strategy->_heal();
	_update_health_bar();
}

void godot::PlayerController::_set_damage(float value)
{
	current_player_strategy->_set_damage(value);
}

float godot::PlayerController::_get_damage()
{
	return current_player_strategy->_get_damage();
}

void godot::PlayerController::_set_attack_speed_delta(float value)
{
	attack_speed_delta = value > 0 ? value : 0.0f;
}

float godot::PlayerController::_get_attack_speed_delta()
{
	return attack_speed_delta;
}

void godot::PlayerController::_die()
{
	if (door != nullptr)
	{
		auto camera = CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D");
		camera->call("_door_collision", "-" + door->get_name());
	}
	is_alive = false;

	prev_state = current_player_strategy->_clone();

	is_alive = false;

	prev_state = current_player_strategy->_clone();
	if (current_player_strategy->_was_revived())
	{
		is_ghost_mode = true;
		current_player_strategy->_set_strategy(player_producer->_get_player_ghost(this, bullet_prefab));
		_restore_data();
		return;
	}

	current_player_strategy->_set_was_revived(true);
	add_child(revive_zone->instance());
	current_player_strategy->_set_strategy(player_producer->_get_player_died(this, bullet_prefab));
	_restore_data();
	current_player_strategy->_get_health_bar()->set_value(0);
}

void godot::PlayerController::_revive()
{
	revive_particles->set_emitting(true);
	current_player_strategy->_revive();
	is_alive = true;
	Ref<PackedScene> prefab = nullptr;
	prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/SoundsEffects/Effects/PlayerRevive.tscn");
	add_child(prefab->instance());
	current_player_strategy->_set_strategy(player_producer->_get_player(this, bullet_prefab));
	_restore_data();
	_set_max_HP(prev_state->_get_max_HP());
	_set_HP(_get_max_HP() * (float)0.15);
}

float godot::PlayerController::_get_max_HP()
{
	return current_player_strategy->_get_max_HP();
}

void godot::PlayerController::_set_max_HP(float value)
{
	current_player_strategy->_set_max_HP(value);
}

void godot::PlayerController::_on_enemy_die(Vector2 enemy_position)
{
	item_generator->_dead_enemy(enemy_position);
}

bool godot::PlayerController::_is_alive()
{
	return is_alive;
}

void godot::PlayerController::_start_item_particles(bool is_buff)
{
	_update_max_health_bar_size();

	if (is_buff)
		buff_debuff_particles->get_process_material()->set("hue_variation", .85);
	else
		buff_debuff_particles->get_process_material()->set("hue_variation", -.85);

	buff_debuff_particles->restart();
}

void godot::PlayerController::_update_health_bar()
{
	current_player_strategy->_update_health_bar();
}

void godot::PlayerController::_update_max_health_bar_size()
{
	current_player_strategy->_get_health_bar()->set_max(current_player_strategy->_get_max_HP());
	current_player_strategy->_update_health_bar();
}

void godot::PlayerController::_animate_spider_web()
{
	cast_to<AnimatedSprite>(get_node("SpiderWeb"))->set_frame(0);
	cast_to<AnimatedSprite>(get_node("SpiderWeb"))->play("idle");
}

void godot::PlayerController::_show_tutorial_message(Node* node)
{
	cast_to<VBoxContainer>(CustomExtensions::GetChildByName(node, "Stuff"))->set_visible(true);
}

void godot::PlayerController::_hide_tutorial_message(Node* node)
{
	cast_to<VBoxContainer>(CustomExtensions::GetChildByName(node, "Stuff"))->set_visible(false);
}

void godot::PlayerController::_stop_animations()
{
	current_player_strategy->_stop_animations();
}

void godot::PlayerController::_player_fight()
{
	current_player_strategy->_fight();
}

void godot::PlayerController::_restore_data()
{
	std::map<String, String> controll_buttons = prev_state->_get_controll_buttons();
	
	_set_controll_buttons(controll_buttons["move_up"], controll_buttons["move_down"],
		controll_buttons["move_left"], controll_buttons["move_right"], controll_buttons["fight_up"], controll_buttons["fight_down"],
		controll_buttons["fight_left"], controll_buttons["fight_right"], controll_buttons["special"]);
	
	controll_buttons.clear();

	_set_max_HP(prev_state->_get_max_HP());
	_set_damage(prev_state->_get_damage());
	_set_speed(prev_state->_get_speed());
	_set_was_revived(prev_state->_was_revived());
}

void godot::PlayerController::_stay_ghost()
{
	is_alive = false;

	prev_state = current_player_strategy->_clone();
	if (current_player_strategy->_was_revived())
	{
		current_player_strategy->_set_strategy(player_producer->_get_player_ghost(this, bullet_prefab));
		_restore_data();
	}
}

void godot::PlayerController::_set_was_revived(bool value)
{
	current_player_strategy->_set_was_revived(value);
}

void godot::PlayerController::_ghost_to_player()
{
	prev_state = current_player_strategy->_clone();
	current_player_strategy->_set_strategy(player_producer->_get_player(this, bullet_prefab));
	_restore_data();
	_set_HP(_get_max_HP());
	_update_health_bar();
	current_player_strategy->_set_was_revived(false);
}

void godot::PlayerController::_set_controll_buttons(String move_up, String move_down, String move_left, String move_right, String fight_up, String fight_down, String fight_left, String fight_right, String special)
{
	current_player_strategy->_set_controll_buttons(move_up, move_down, move_left, move_right, fight_up, fight_down, fight_left, fight_right, special);
}
