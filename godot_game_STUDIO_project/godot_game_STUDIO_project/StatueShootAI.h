#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class StatueShootAI : public IEnemyAI, public KinematicBody2D
	{
		Vector2 directions[4];
		std::vector<Node2D*> bullets;
		int max_bullet_count;
		Node2D* enemy;
		bool can_fight;

	public:
		StatueShootAI(Ref<PackedScene>& bullet, Node2D* node, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _process(float delta, Node2D* enemy = nullptr, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void _remove_side(int side);
		void _change_dir_after_time();
		void _delete_player1(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _delete_player2(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		String _get_current_player();
		void _set_speed(float value);
	};
}