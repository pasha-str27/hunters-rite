#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::FlowerAI::FlowerAI(Ref<PackedScene>& bullet, Node2D *node_tmp, Node2D* player1, Node2D* player2):
	EnemyData(node_tmp, player1, player2)
{
	max_bullet_count = 5 * 8;
	can_fight = true;

	auto node = _get_enemy()->get_parent()->get_child(0);

	for (int i = 0; i < max_bullet_count; ++i)
	{
		auto new_obj = bullet->instance();
		node->add_child(new_obj);
		bullets.push_back(cast_to<Node2D>(new_obj));
	}

	directions[0] = Vector2::UP;
	directions[2] = Vector2::RIGHT;
	directions[4] = Vector2::DOWN;
	directions[6] = Vector2::LEFT;

	directions[1] = Vector2(0.5, 0.5);
	directions[3] = Vector2(0.5, -0.5);
	directions[5] = Vector2(-0.5, 0.5);
	directions[7] = Vector2(-0.5, -0.5);
}

void godot::FlowerAI::_add_bullet(Node* node)
{
	bullets.push_back(cast_to<Node2D>(node));
}

void godot::FlowerAI::change_can_fight(bool value)
{
	can_fight = value;
}

void godot::FlowerAI::_set_speed(float value)
{
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
			if (bullets.size() > 0)
			{
				bullets[bullets.size() - 1]->set_position(_get_enemy()->get_global_position());
				bullets[bullets.size() - 1]->set_visible(true);

				bullets[bullets.size() - 1]->call("_set_dir", directions[i]);

				if (bullets.size() == 1)
				{
					auto node = _get_enemy()->get_parent()->get_child(0);
					auto new_obj = bullets[0]->duplicate(8);
					node->add_child(new_obj);
					bullets.push_back(cast_to<Node2D>(new_obj));
				}

				bullets.pop_back();
			}
		}

		_get_enemy()->call("_start_timer");
	}
}