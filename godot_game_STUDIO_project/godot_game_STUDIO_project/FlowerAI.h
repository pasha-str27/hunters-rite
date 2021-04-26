#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class FlowerAI : public IEnemyAI, public KinematicBody2D
	{
		Vector2 directions[8];

	public:
		FlowerAI();
		void _process(float delta, Node2D* enemy = nullptr, Node2D* player1 = nullptr, Node2D* player2 = nullptr);
	};
}
