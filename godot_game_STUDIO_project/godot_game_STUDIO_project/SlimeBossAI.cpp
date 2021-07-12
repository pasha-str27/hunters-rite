#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::SlimeBossAI::SlimeBossAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	can_move = true;
	_attack_state = new SlimeAttackSpawnState(this);
	target_player = empty_pos;

	auto bullet_container = node_tmp->get_parent()->get_node("BulletContainer");

	bullet_pull = new BulletPull(max_bullet_count, bullet, bullet_container);

	jump_zone = cast_to<Node2D>(_get_enemy()->get_parent()->get_node("jump_zone"));
	wave_node = cast_to<Node2D>(_get_enemy()->get_parent()->get_node("DamageWave"));
	Array arr = CameraController::current_room->call("_get_enemy_spawn_positions");
	places_to_spawn = arr[0];
	enemies_to_spawn = _get_enemy()->get_node("EnemiesHolder")->call("_get_enemies_list");
	camera_shake = _get_enemy()->get_node("/root/Node2D/Node/Camera2D")->get_node("CameraShake");
}

godot::SlimeBossAI::~SlimeBossAI()
{
	delete bullet_pull;
	camera_shake = nullptr;
}

void godot::SlimeBossAI::_set_player(Node2D* player)
{
	target_player = player->get_global_position();
}

void godot::SlimeBossAI::_remove_player(Node2D* player)
{
	if (player->is_in_group("player1"))
		_delete_player1();

	if (player->is_in_group("player2"))
		_delete_player2();
}

void godot::SlimeBossAI::_change_state(ISlimeAttackState* state)
{
	_attack_state = state;
}

void godot::SlimeBossAI::change_can_fight(bool value, ISlimeAttackState* state)
{
	can_move = value;
	
	_attack_state = state;
}

void godot::SlimeBossAI::_wait(float time)
{
	_get_enemy()->call("_start_fixed_timer", time);
}

void godot::SlimeBossAI::_add_bullet(Node* node)
{
	bullet_pull->_add_bullet(cast_to<Node2D>(node));
}

void godot::SlimeBossAI::_shoot()
{
	change_can_fight(false);

	if (target_player == empty_pos)
		return;

	Vector2 bullet_dir = target_player;
	Vector2 bullet_position = _get_enemy()->get_global_position();

	std::vector<Node2D*> bullets;

	for (int i = 0; i < 3; ++i)
	{
		bullets.push_back(bullet_pull->_get_bullet());
		bullets[i]->set_global_position(bullet_position);
	}

	float angle = M_PI / 18;
	Vector2 bullet_directions[3];
	bullet_directions[0] = (bullet_dir - bullets[0]->get_global_position()).normalized();
	bullet_directions[1] = Vector2::ZERO;
	bullet_directions[2] = Vector2::ZERO;

	bullet_directions[1].x = bullet_directions[0].x * cos(angle) - bullet_directions[0].y * sin(angle);
	bullet_directions[1].y = bullet_directions[0].x * sin(angle) + bullet_directions[0].y * cos(angle);

	bullet_directions[2].x = bullet_directions[0].x * cos(-angle) - bullet_directions[0].y * sin(-angle);
	bullet_directions[2].y = bullet_directions[0].x * sin(-angle) + bullet_directions[0].y * cos(-angle);

	for (int i = 0; i < 3; i++)
	{
		bullets[i]->set_visible(true);
		bullets[i]->call("_set_dir", bullet_directions[i]);
	}		

	bullets.clear();

	_wait(1.5f);
}

void godot::SlimeBossAI::_spawn_enemy()
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	Vector2 pos = places_to_spawn[rng->randi_range(0, places_to_spawn.size() - 1)];
	Ref<PackedScene> enemy_prefab = enemies_to_spawn[rng->randi_range(0, enemies_to_spawn.size() - 1)];
	auto enemy = cast_to<Node2D>(enemy_prefab->instance());
	_get_enemy()->get_node("/root/Node2D/Node")->call_deferred("add_child", enemy);
	enemy->set_global_position(pos);
	for (int i = 0; i < enemy->get_child_count(); ++i)
		if (enemy->get_child(i)->has_method("_change_start_parameters"))
		{
			enemy->get_child(i)->call_deferred("_change_start_parameters");
			return;
		}
}

void godot::SlimeBossAI::_jump()
{
	is_jumping = true;
	jumping_up = true;
	goal = _get_enemy()->get_global_position() - Vector2(0, 720);
	_disable_collisions();
}

void godot::SlimeBossAI::_jumping(float delta)
{
	_get_enemy()->set_global_position(_get_enemy()->get_global_position().move_toward(goal, delta * 1000));

	if (abs(goal.distance_to(_get_enemy()->get_global_position())) <= 1)
	{
		is_jumping = false;
		if (jumping_up)
		{
			_set_target();
			_get_enemy()->set_global_position(Vector2(target_player.x, _get_enemy()->get_global_position().y));
			_show_jump_zone();
		}
		else
		{
			camera_shake->call("_start", 10, .35f);
			_enable_collisions();
			jump_zone->set_visible(false);
			_wait(1);
		}
	}
}

void godot::SlimeBossAI::_show_jump_zone()
{
	jump_zone->set_global_position(target_player);
	cast_to<AnimationPlayer>(jump_zone->get_node("Animator"))->play("grow");
	_start_falling();
}

void godot::SlimeBossAI::_start_falling()
{
	goal = target_player;
	is_jumping = true;
	jumping_up = false;
}

void godot::SlimeBossAI::_set_target()
{
	if (MenuButtons::game_mode == COOP)
	{
		Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
		rng->randomize();
		if (rng->randi_range(1, 2) == 1)
		{
			if (_get_player1() != nullptr)
				target_player = _get_player1()->get_global_position();
			else if (_get_player2() != nullptr)
				target_player = _get_player2()->get_global_position();
			else
				target_player = empty_pos;
		}
		else
		{
			if (_get_player2() != nullptr)
				target_player = _get_player2()->get_global_position();
			else if (_get_player1() != nullptr)
				target_player = _get_player1()->get_global_position();
			else
				target_player = empty_pos;
		}
	}
	else
	{
		if (MenuButtons::game_mode == SHOOTER)
			target_player = _get_player1()->get_global_position();
		else if (MenuButtons::game_mode == MELEE)
				target_player = _get_player2()->get_global_position();
	}


	if (target_player.x > _get_enemy()->get_global_position().x)
		cast_to<AnimatedSprite>(_get_enemy()->find_node("AnimatedSprite"))->set_flip_h(true);
	else
		cast_to<AnimatedSprite>(_get_enemy()->find_node("AnimatedSprite"))->set_flip_h(false);
}

void godot::SlimeBossAI::_disable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, false);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, false);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, false);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, false);
}

void godot::SlimeBossAI::_enable_collisions()
{
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_layer_bit(0, true);
	cast_to<Area2D>(_get_enemy()->get_node("Area2D"))->set_collision_mask_bit(0, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_mask_bit(9, true);
	cast_to<KinematicBody2D>(_get_enemy())->set_collision_layer_bit(2, true);
}

void godot::SlimeBossAI::_make_wave()
{

}

void godot::SlimeBossAI::change_can_fight(bool value)
{
	can_move = value;
}

void godot::SlimeBossAI::_fight(Node2D* player1, Node2D* player2)
{
	if (can_move)
	{
		can_move = false;
		_attack_state->_fight();
	}

}

void godot::SlimeBossAI::_process(float delta)
{
	if (is_jumping)
		_jumping(delta);

	_fight();
}

void godot::SlimeBossAI::_set_speed(float value)
{
	speed = value;
}
