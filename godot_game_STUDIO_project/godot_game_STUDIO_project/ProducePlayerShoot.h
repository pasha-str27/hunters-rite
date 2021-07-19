#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class ProducePlayerShoot :	public PlayerProduce
	{
	public:
		IPlayer* _get_player(Node2D* object, Ref<PackedScene> bullet = 0);
		IPlayer* _get_player_died(Node2D* object, Ref<PackedScene> bullet = 0);
		IPlayer* _get_player_ghost(Node2D* object, Ref<PackedScene> bullet = 0);
;	};
}

