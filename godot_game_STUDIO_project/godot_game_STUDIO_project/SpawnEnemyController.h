#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot 
{
	class ItemsContainer;
	class SpawnEnemyController: public Node2D
	{
	private:
		GODOT_CLASS(SpawnEnemyController, Node2D);
		void SpawnEnemies();
		void SpawnBoss();
		void SpawnItems();
		void SpawnKey();
		ItemsContainer* i_container = nullptr;
		Ref<PackedScene> altar = nullptr;
		Ref<PackedScene> pedestal = nullptr;
		Timer* timer = nullptr;
		int levels_count = 7;
		String current_level = "";

	public:
		Array enemies = {};
		Array spawn_points = {};
		int enemies_count = 5;

		static void _register_methods();
		void _init();
		void _ready();
		
		void _prepare_spawn();
		void _spawn();
		void _on_Area2D_area_entered(Node* other);
		void _stand_random_level();
		String _get_current_level_name();
		SpawnEnemyController();
		~SpawnEnemyController();
	};
}


