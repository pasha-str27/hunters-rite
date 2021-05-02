#include "SpawnEnemyController.h"

void godot::SpawnEnemyController::SpawnEnemies()
{
	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();
	
	for (int i = 0; i < enemies_count; i++) {
		int rand_point = rng->randi_range(0, spawn_points.size() - 1);
		int rand_enemy = rng->randi_range(0, enemies.size() - 1);
		auto spawned_enemy = cast_to<Node2D>(cast_to<PackedScene>(enemies[rand_enemy])->instance());
		spawned_enemy->set_global_position(cast_to<Node2D>(spawn_points[rand_point])->get_global_position());
		spawn_points.remove(rand_point);
		add_child(spawned_enemy, true);
	}

	rng = nullptr;
}

void godot::SpawnEnemyController::_register_methods()
{
	register_method("_ready", &SpawnEnemyController::_ready);
	register_method("_prepare_spawn", &SpawnEnemyController::_prepare_spawn);

	register_property<SpawnEnemyController, Array>("Enemies", &SpawnEnemyController::enemies, {});
	register_property<SpawnEnemyController, int>("Enemies Count", &SpawnEnemyController::enemies_count, 0);
}

void godot::SpawnEnemyController::_init()
{
	enemies_count = 5;
}

void godot::SpawnEnemyController::_ready()
{
	_prepare_spawn();
}

void godot::SpawnEnemyController::_prepare_spawn()
{
	spawn_points = get_node("SpawnPoints")->get_children();
	SpawnEnemies();
}

godot::SpawnEnemyController::SpawnEnemyController()
{
}

godot::SpawnEnemyController::~SpawnEnemyController()
{
	enemies = {};
	spawn_points = {};
}
