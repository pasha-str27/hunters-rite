#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerProduce
	{
	public:
		virtual IPlayer* _get_player(Node2D* object, Ref<PackedScene>bullet = 0) = 0;
	};
}