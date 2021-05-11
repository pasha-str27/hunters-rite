#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SpawnEnemyController::SpawnEnemies()
{

	if (spawn_points.size() == 0) 
	{
		CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->call("_open_doors");
		return;
	}

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();
	
	for (int i = 0; i < enemies_count; i++) 
	{
		int rand_point = rng->randi_range(0, (int64_t)spawn_points.size() - 1);
		int rand_enemy = rng->randi_range(0, (int64_t)enemies.size() - 1);
		auto spawned_enemy = cast_to<Node2D>(cast_to<PackedScene>(enemies[rand_enemy])->instance());
		spawned_enemy->set_global_position(cast_to<Node2D>(spawn_points[rand_point])->get_global_position());
		spawn_points.remove(rand_point);
		get_node("/root/Node2D/Node")->call_deferred("add_child", spawned_enemy);
	}

	rng = nullptr;
}

void godot::SpawnEnemyController::_register_methods()
{
	register_method("_ready", &SpawnEnemyController::_ready);
	register_method("_prepare_spawn", &SpawnEnemyController::_prepare_spawn);
	register_method("_on_Area2D_area_entered", &SpawnEnemyController::_on_Area2D_area_entered);
	
	register_property<SpawnEnemyController, Array>("Enemies", &SpawnEnemyController::enemies, {});
	register_property<SpawnEnemyController, int>("Enemies Count", &SpawnEnemyController::enemies_count, 0);
}

void godot::SpawnEnemyController::_init()
{
	enemies_count = 5;
}

void godot::SpawnEnemyController::_ready()
{

}

void godot::SpawnEnemyController::_prepare_spawn()
{
	SpawnEnemies();
	if(Enemies::get_singleton()->_get_enemies_count() > 0)
		get_parent()->call("_close_doors");

	spawn_points.clear();
}

void godot::SpawnEnemyController::_on_Area2D_area_entered(Node* other)
{
	if (other->is_in_group("room")) 
	{
		spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
		//_prepare_spawn();
		other->queue_free();
	}

	if (other->is_in_group("item_room")) 
	{
		// spawn items
	}
}

godot::SpawnEnemyController::SpawnEnemyController()
{
}

godot::SpawnEnemyController::~SpawnEnemyController()
{
	enemies = {};
	spawn_points = {};
}
