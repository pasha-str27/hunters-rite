#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Spike : public TileMap
	{
		GODOT_CLASS(Spike, TileMap);

		float damage;

	public:
		static void _register_methods();
		Spike();
		void _init();
		float _get_damage();
	};
}