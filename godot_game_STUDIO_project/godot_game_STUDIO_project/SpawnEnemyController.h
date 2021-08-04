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

		ItemsContainer* i_container = nullptr;
		Ref<PackedScene> altar = nullptr;
		Ref<PackedScene> boss_prefab = nullptr;
		Ref<PackedScene> pedestal = nullptr;
		Ref<PackedScene> boss_slime_prefab = nullptr;
		Ref<PackedScene> naga_boss_prefab = nullptr;
		Ref<PackedScene> spider_prefab = nullptr;
		Ref<PackedScene> tutorial_enemy = nullptr;
		Timer* timer = nullptr;
		Array enemy_list_prefabs = {};

	public:
		static void _register_methods();
		void _init();
		void _ready();		
		void _prepare_spawn();
		void _spawn();
		float _calculate_room_difficulty();
		float _find_min_enemy_price();
		void _spawn_boss(Ref<PackedScene> boss_prefab);
		std::vector<Vector2> _fill_enemies();
		SpawnEnemyController();
		~SpawnEnemyController();
	};
}
