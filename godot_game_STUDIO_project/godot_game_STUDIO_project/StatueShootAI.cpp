#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif


godot::StatueShootAI::StatueShootAI(Ref<PackedScene>& bullet, Node2D* node_tmp, Node2D* player1, Node2D* player2)
{
	max_bullet_count = 20;
	enemy = node_tmp;
	can_fight = true;

	auto node = node_tmp->get_node("/root/Node2D/Node/BulletConteinerStatue");

	for (int i = 0; i < max_bullet_count; ++i)
	{
		auto new_obj = bullet->instance();
		node->add_child(new_obj);
		bullets.push_back(cast_to<Node2D>(new_obj));
	}

	directions[0] = Vector2::UP;
	directions[1] = Vector2::RIGHT;
	directions[2] = Vector2::DOWN;
	directions[3] = Vector2::LEFT;
}

void godot::StatueShootAI::_add_bullet(Node* node)
{
	bullets.push_back(cast_to<Node2D>(node));
}

void godot::StatueShootAI::change_can_fight(bool value)
{
	can_fight = value;
}

void godot::StatueShootAI::_remove_side(int side)
{
}

void godot::StatueShootAI::_change_dir_after_time()
{
}

void godot::StatueShootAI::_delete_player1(Node2D* player1, Node2D* player2)
{
}

void godot::StatueShootAI::_delete_player2(Node2D* player1, Node2D* player2)
{
}

String godot::StatueShootAI::_get_current_player()
{
	return String();
}

void godot::StatueShootAI::_set_speed(float value)
{
}

void godot::StatueShootAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	if (can_fight)
	{
		for (int i = 0; i < 4; ++i)
		{
			Vector2 point = directions[i];
			directions[i].x = point.x * cos(M_PI / 4) - point.y * sin(M_PI / 4);
			directions[i].y = point.x * sin(M_PI / 4) + point.y * cos(M_PI/4);
		}

		can_fight = false;

		for (int i = 0; i < 4; ++i)
		{
			if (bullets.size() > 0)
			{
				bullets[bullets.size() - 1]->set_position(enemy->get_global_position());
				bullets[bullets.size() - 1]->set_visible(true);

				bullets[bullets.size() - 1]->call("_set_dir", directions[i]);

				if (bullets.size() == 1)
				{
					auto node = enemy->get_node("/root/Node2D/Node/BulletConteinerStatue");
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