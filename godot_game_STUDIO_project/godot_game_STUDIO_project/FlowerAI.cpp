#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

godot::FlowerAI::FlowerAI(Ref<PackedScene>& bullet, Node2D *node_tmp)
{
	max_bullet_count = 5 * 8;
	enemy = node_tmp;
	can_fight = true;

	auto node = node_tmp->get_node("/root/Node2D/Node/BulletConteinerFlower");

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

void godot::FlowerAI::_remove_side(int side)
{
}

void godot::FlowerAI::_change_dir_after_time()
{
}

void godot::FlowerAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	enemy->rotate(delta / 3);

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
				bullets[bullets.size() - 1]->set_position(enemy->get_global_position());
				bullets[bullets.size() - 1]->set_visible(true);

				bullets[bullets.size() - 1]->call("_set_dir", directions[i]);

				if (bullets.size() == 1)
				{
					auto node = enemy->get_node("/root/Node2D/Node/BulletConteinerFlower");
					auto new_obj = bullets[0]->duplicate(8);
					node->add_child(new_obj);
					bullets.push_back(cast_to<Node2D>(new_obj));
				}

				bullets.pop_back();
			}
		}

		enemy->call("_start_timer");
	}
}
