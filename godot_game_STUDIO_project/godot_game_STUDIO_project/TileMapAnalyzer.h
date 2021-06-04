#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class TileMapAnalyzer : public TileMap
	{
		GODOT_CLASS(TileMapAnalyzer, TileMap);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		TileMapAnalyzer();
		~TileMapAnalyzer();
	};
}

