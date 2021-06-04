#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::TileMapAnalyzer::_register_methods()
{
	register_method("_init", &TileMapAnalyzer::_init);
	register_method("_ready", &TileMapAnalyzer::_ready);
}

void godot::TileMapAnalyzer::_init()
{
}

void godot::TileMapAnalyzer::_ready()
{
	//for (int i = 0; i < get_used_cells().size();++i)
	//	Godot::print(get_used_cells()[i]);
}

godot::TileMapAnalyzer::TileMapAnalyzer()
{
}

godot::TileMapAnalyzer::~TileMapAnalyzer()
{
}
