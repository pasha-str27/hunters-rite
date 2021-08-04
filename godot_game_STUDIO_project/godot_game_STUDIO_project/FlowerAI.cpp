#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::FlowerAI::FlowerAI(Ref<PackedScene>& bullet, Node2D *node_tmp) : EnemyData(node_tmp)
{
	max_bullet_count = 5 * 8;
	can_fight = true;

	auto node = _get_enemy()->get_parent()->get_child(0);

	bullet_pull = new BulletPull(max_bullet_count, bullet, node);

	directions[0] = Vector2::UP;
	directions[2] = Vector2::RIGHT;
	directions[4] = Vector2::DOWN;
	directions[6] = Vector2::LEFT;

	directions[1] = Vector2(0.5, 0.5);
	directions[3] = Vector2(0.5, -0.5);
	directions[5] = Vector2(-0.5, 0.5);
	directions[7] = Vector2(-0.5, -0.5);
}

godot::FlowerAI::~FlowerAI()
{
	delete bullet_pull;
}

void godot::FlowerAI::_add_bullet(Node* node)
{
	bullet_pull->_add_bullet(cast_to<Node2D>(node));
}

void godot::FlowerAI::change_can_fight(bool value)
{
	can_fight = value;
}

void godot::FlowerAI::_set_speed(float value)
{
}

void godot::FlowerAI::_change_start_parameters()
{
	Vector2 cur_pos = (_get_enemy()->get_global_position() - 
		CurrentRoom::get_singleton()->_get_current_room()->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
	for (int i = cur_pos.x - 1; i <= cur_pos.x + 1; ++i)
		for (int j = cur_pos.y - 1; j <= cur_pos.y + 1; ++j)
			CurrentRoom::get_singleton()->_get_current_room()->call("_set_cell_value", j, i, 8);
}

void godot::FlowerAI::_remove_taken_positions()
{
	Vector2 cur_pos = (_get_enemy()->get_global_position() - 
		CurrentRoom::get_singleton()->_get_current_room()->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
	for (int i = cur_pos.x - 1; i <= cur_pos.x + 1; ++i)
		for (int j = cur_pos.y - 1; j <= cur_pos.y + 1; ++j)
			CurrentRoom::get_singleton()->_get_current_room()->call("_set_cell_value", j, i, 0);
}

void godot::FlowerAI::_process(float delta)
{
	_get_enemy()->rotate(delta / 3);

	for (int i = 0; i < 8; ++i)
	{
		directions[i].x = directions[i].x * cos(delta / 3) - directions[i].y * sin(delta / 3);
		directions[i].y = directions[i].x * sin(delta / 3) + directions[i].y * cos(delta / 3);
	}

	if (can_fight)
	{
		can_fight = false;
		for (int i = 0; i < 8; ++i)
		{
			Node2D* bullet = bullet_pull->_get_bullet();
			bullet->set_position(_get_enemy()->get_global_position());
			bullet->set_visible(true);

			bullet->call("_set_dir", directions[i]);
		}

		_get_enemy()->call("_start_timer");
	}
}