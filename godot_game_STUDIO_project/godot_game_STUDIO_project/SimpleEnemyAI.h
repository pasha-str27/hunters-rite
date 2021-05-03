#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SimpleEnemyAI : public IEnemyAI, public KinematicBody2D
	{
	public:
		void _process(float delta, Node2D* enemy = nullptr, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* bullet);
		void change_can_fight(bool value);
		void _remove_side(int side);
		void _change_dir_after_time();
	};
}