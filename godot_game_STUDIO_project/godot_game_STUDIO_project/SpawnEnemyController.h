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
		ItemsContainer* i_container = nullptr;
		Ref<PackedScene> altar = nullptr;
	public:
		Array enemies = {};
		Array spawn_points = {};
		int enemies_count = 5;

		static void _register_methods();
		void _init();
		void _ready();
		
		void _prepare_spawn();
		void _on_Area2D_area_entered(Node* other);
		
		SpawnEnemyController();
		~SpawnEnemyController();
	};
}


