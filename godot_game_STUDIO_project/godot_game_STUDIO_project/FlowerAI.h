#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class FlowerAI : public EnemyData, public KinematicBody2D
	{
		Vector2 directions[8];
		std::vector<Node2D*> bullets;
		int max_bullet_count;
		bool can_fight;

	public:
		FlowerAI(Ref<PackedScene> &bullet, Node2D* node);
		~FlowerAI();
		void _process(float delta);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void _set_speed(float value);
		void _change_start_parameters();
	};
}