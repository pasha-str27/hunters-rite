#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

godot::FlowerAI::FlowerAI()
{
	directions[0] = Vector2::UP;
	directions[2] = Vector2::RIGHT;
	directions[4] = Vector2::DOWN;
	directions[6] = Vector2::LEFT;

	directions[1] = Vector2(0.5, 0.5);
	directions[3] = Vector2(0.5, -0.5);
	directions[5] = Vector2(-0.5, 0.5);
	directions[7] = Vector2(-0.5, -0.5);
}

void godot::FlowerAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	enemy->rotate(delta/5);
	
	for (int i = 0; i < 8; ++i)
	{
		directions[i].x = directions[i].x * cos(delta / 5) - directions[i].y * sin(delta / 5);
		directions[i].y = directions[i].x * sin(delta / 5) + directions[i].y * cos(delta / 5);
	}

}
