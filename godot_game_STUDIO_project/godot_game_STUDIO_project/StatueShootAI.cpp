#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::StatueShootAI::StatueShootAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : EnemyData(node_tmp)
{
	can_fight = true;

	auto node = _get_enemy()->get_parent()->get_child(0);

	bullet_pull = new BulletPull(max_bullet_count, bullet, node);

	directions[0] = Vector2::UP;
	directions[1] = Vector2::RIGHT;
	directions[2] = Vector2::DOWN;
	directions[3] = Vector2::LEFT;
}

godot::StatueShootAI::~StatueShootAI()
{
	delete bullet_pull;
}

void godot::StatueShootAI::_add_bullet(Node* node)
{
	bullet_pull->_add_bullet(cast_to<Node2D>(node));
}

void godot::StatueShootAI::change_can_fight(bool value)
{
	can_fight = value;
}

void godot::StatueShootAI::_change_start_parameters()
{
	Vector2 cur_pos = (_get_enemy()->get_global_position() - CurrentRoom::get_singleton()->_get_current_room()->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
	CurrentRoom::get_singleton()->_get_current_room()->call("_set_cell_value", cur_pos.y, cur_pos.x, 8);
}

void godot::StatueShootAI::_remove_taken_positions()
{
	Vector2 cur_pos = (_get_enemy()->get_global_position() - CurrentRoom::get_singleton()->_get_current_room()->get_global_position() + Vector2(896, 544) / 2 - Vector2(16, 16)) / 32;
	CurrentRoom::get_singleton()->_get_current_room()->call("_set_cell_value", cur_pos.y, cur_pos.x, 0);
}

void godot::StatueShootAI::_process(float delta)
{
	if (can_fight)
	{
		for (int i = 0; i < 4; ++i)
		{
			Vector2 point = directions[i];
			directions[i].x = point.x * cos(M_PI / 4) - point.y * sin(M_PI / 4);
			directions[i].y = point.x * sin(M_PI / 4) + point.y * cos(M_PI / 4);
		}

		can_fight = false;

		for (int i = 0; i < 4; ++i)
		{
			Node2D* bullet = bullet_pull->_get_bullet();

			bullet->set_position(_get_enemy()->get_global_position());
			bullet->set_visible(true);
			bullet->call("_set_dir", directions[i]);
		}

		_get_enemy()->call("_start_timer");
	}
}