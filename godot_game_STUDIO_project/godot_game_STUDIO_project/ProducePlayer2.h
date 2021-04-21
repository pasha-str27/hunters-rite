#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class ProducePlayer2 : public PlayerProduce
	{
	public:
		IPlayer* get_player(Node2D* object, Ref<PackedScene>bullet = 0);
	};
}