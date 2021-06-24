#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class StatueShootAI : public EnemyData, public KinematicBody2D
	{
		Vector2 directions[4];
		std::vector<Node2D*> bullets;
		int max_bullet_count;
		bool can_fight;

	public:
		StatueShootAI(Ref<PackedScene>& bullet, Node2D* node);
		~StatueShootAI();
		void _process(float delta);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void _set_speed(float value);
		void _change_start_parameters();
	};
}