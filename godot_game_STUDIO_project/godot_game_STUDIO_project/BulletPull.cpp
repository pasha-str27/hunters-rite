#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::BulletPull::BulletPull(int max_bullet_count, Ref<PackedScene> bullet, Node* parent_node)
{
	this->bullet_prefab = bullet;
	this->parent_node = parent_node;

	for (int i = 0; i < max_bullet_count; ++i)
	{
		auto new_obj = bullet->instance();
		parent_node->add_child(new_obj);
		bullets.push_back(parent_node->cast_to<Node2D>(new_obj));
	}
}

godot::BulletPull::BulletPull()
{
}

godot::BulletPull::~BulletPull()
{
	bullets.clear();
	parent_node = nullptr;
}

Node2D* godot::BulletPull::_get_bullet()
{
	Node2D* bullet = nullptr;
	if (bullets.size() > 0)
	{
		if (bullets.size() == 1)
		{
			auto new_obj = bullets[0]->duplicate(8);
			parent_node->add_child(new_obj);
			bullets.push_back(parent_node->cast_to<Node2D>(new_obj));
		}

		bullet = bullets[bullets.size() - 1];
		bullets.pop_back();
	}
	return bullet;
}

void godot::BulletPull::_add_bullet(Node2D* bullet)
{
	bullets.push_back(bullet);
}
