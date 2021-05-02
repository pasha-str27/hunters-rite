#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif
namespace godot {
	class SpawnEnemyController: public Node2D
	{
	private:
		GODOT_CLASS(SpawnEnemyController, Node2D);
		void SpawnEnemies();
	public:
		Array enemies = {};
		Array spawn_points = {};
		int enemies_count = 5;

		static void _register_methods();
		void _init();
		void _ready();

		void _prepare_spawn();

		
		SpawnEnemyController();
		~SpawnEnemyController();
	};
}


