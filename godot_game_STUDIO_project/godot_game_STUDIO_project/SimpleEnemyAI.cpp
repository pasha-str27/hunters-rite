#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

void godot::SimpleEnemyAI::_process(float delta, Node2D* enemy, Node2D* player1, Node2D* player2)
{
	//if (enemy != nullptr)
	//	cast_to<KinematicBody2D>(enemy)->move_and_slide(/*Vector2::UP*25*/player1->get_global_position().normalized()*25);
}

void godot::SimpleEnemyAI::_add_bullet(Node* bullet)
{
}

void godot::SimpleEnemyAI::change_can_fight(bool value)
{
}
