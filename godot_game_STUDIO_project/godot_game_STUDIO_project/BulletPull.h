#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BulletPull
	{
		int max_bullet_count;
		std::vector<Node2D*> bullets;
		Node* parent_node = nullptr;
		Ref<PackedScene> bullet_prefab = nullptr;
	public:
		BulletPull(int max_bullet_count, Ref<PackedScene> bullet, Node* parent_node);
		BulletPull();
		~BulletPull();
		Node2D* _get_bullet();
		void _add_bullet(Node2D* bullet);
	};
}