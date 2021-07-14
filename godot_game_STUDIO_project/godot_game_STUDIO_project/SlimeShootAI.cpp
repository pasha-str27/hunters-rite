#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::SlimeShootAI::SlimeShootAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : SlimeAI(bullet, node_tmp)
{
	auto bullet_container = node_tmp->get_parent()->get_node("BulletConteiner");

	bullet_pull = new BulletPull(max_bullet_count, bullet, bullet_container);
}

godot::SlimeShootAI::~SlimeShootAI()
{
	delete bullet_pull;
}

void godot::SlimeShootAI::_fight(Node2D* player1, Node2D* player2)
{
	change_can_fight(false);
	_get_enemy()->call("_start_timer");

	if (first_player == nullptr)
		return;

	_get_enemy()->call("_change_animation", "attack", 5);

	Vector2 bullet_dir = first_player->get_global_position();

	if (bullet_dir.x > _get_enemy()->get_global_position().x)
		cast_to<AnimatedSprite>(_get_enemy()->find_node("AnimatedSprite"))->set_flip_h(true);
	else
		cast_to<AnimatedSprite>(_get_enemy()->find_node("AnimatedSprite"))->set_flip_h(false);

	Node2D* bullet = bullet_pull->_get_bullet();

	bullet->set_global_position(_get_enemy()->get_global_position());

	bullet->set_visible(true);

	bullet->call("_set_dir", (bullet_dir - bullet->get_global_position()).normalized());
}

void godot::SlimeShootAI::_add_bullet(Node* node)
{
	bullet_pull->_add_bullet(node->cast_to<Node2D>(node));
}

void godot::SlimeShootAI::change_direction()
{
	reset_directions();

	if ((int)CurrentRoom::get_singleton()->_get_current_room()->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::LEFT).x) == 0)
		directions.push_back(Vector2::LEFT);

	if ((int)CurrentRoom::get_singleton()->_get_current_room()->call("_get_cell_value", cur_pos.y, (cur_pos + Vector2::RIGHT).x) == 0)
		directions.push_back(Vector2::RIGHT);

	if ((int)CurrentRoom::get_singleton()->_get_current_room()->call("_get_cell_value", (cur_pos + Vector2::DOWN).y, cur_pos.x) == 0)
		directions.push_back(Vector2::DOWN);

	if ((int)CurrentRoom::get_singleton()->_get_current_room()->call("_get_cell_value", (cur_pos + Vector2::UP).y, cur_pos.x) == 0)
		directions.push_back(Vector2::UP);

	PlayersContainer* players = PlayersContainer::_get_instance();

	if (players->_get_player1() == nullptr && players->_get_player1_regular() != nullptr
		&& (bool)players->_get_player1_regular()->call("_is_ghost_mode")
		&& _is_player_near(players->_get_player1_regular()));

	if (players->_get_player2() == nullptr && players->_get_player2_regular() != nullptr
		&& (bool)players->_get_player2_regular()->call("_is_ghost_mode")
		&& _is_player_near(players->_get_player2_regular()));

	_change_dir_after_time();
	_fight();
}

bool godot::SlimeShootAI::_is_player_near(Node2D* player)
{
	Vector2 player_pos_index = (player->get_global_position()
		- CurrentRoom::get_singleton()->_get_current_room()->get_global_position()
		+ Vector2(896, 544) / 2) / 32;

	bool is_player_ghost = (bool)player->call("_is_ghost_mode");

	bool ghost_is_near = false;

	player_pos_index = Vector2((int)player_pos_index.y, (int)player_pos_index.x);

	if (is_player_ghost)
	{
		if (player_pos_index == Vector2((int)cur_pos.y, (int)(cur_pos + Vector2::LEFT).x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::LEFT);
		}

		if (player_pos_index == Vector2((int)cur_pos.y, (int)(cur_pos + Vector2::RIGHT).x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::RIGHT);
		}

		if (player_pos_index == Vector2((int)(cur_pos + Vector2::DOWN).y, (int)cur_pos.x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::DOWN);
		}

		if (player_pos_index == Vector2((int)(cur_pos + Vector2::UP).y, (int)cur_pos.x))
		{
			ghost_is_near = true;
			remove_vector_element(Vector2::UP);
		}
	}

	if (ghost_is_near)
		return true;

	return false;
}

void godot::SlimeShootAI::_set_player(Node2D* player)
{
	if (!player->call("_is_alive"))
		return;

	if (first_player == nullptr)
	{
		first_player = player;
		return;
	}
	second_player = player;
}

void godot::SlimeShootAI::_remove_player(Node2D* player)
{
	if (first_player != nullptr && player->get_name() == first_player->get_name())
	{
		first_player = second_player;
		second_player = nullptr;
		return;
	}
	second_player = nullptr;
}