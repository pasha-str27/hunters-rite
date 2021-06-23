#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

godot::SlimeShootAI::SlimeShootAI(Ref<PackedScene>& bullet, Node2D* node_tmp) : SlimeAI(bullet, node_tmp)
{
}

godot::SlimeShootAI::~SlimeShootAI()
{
}

void godot::SlimeShootAI::_fight(Node2D* player1, Node2D* player2)
{
	Godot::print("fight1");
}
