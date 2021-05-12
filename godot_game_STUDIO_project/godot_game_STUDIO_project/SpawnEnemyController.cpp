#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SpawnEnemyController::SpawnEnemies()
{
	if (spawn_points.size() == 0)
		return;

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

void godot::SpawnEnemyController::SpawnBoss(Node* n)
{
	Array enemies = n->call("_get_enemies");
	auto boss = cast_to<Node2D>(cast_to<PackedScene>(enemies[0])->instance());
	boss->set_global_position(cast_to<Node2D>(get_parent())->get_global_position());
	get_node("/root/Node2D/Node")->add_child(boss, true);
}

void godot::SpawnEnemyController::SpawnItems()
{
	i_container = get_node("/root/Node2D/Node/ItemsContainer")->call("_get_instance");

	Array item_points = get_node("ItemPoints")->get_children();

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();

	for (int i = 0; i < item_points.size(); i++) {
		int index = rng->randi_range(0, i_container->items.size() - 1);
		auto item = cast_to<Node2D>(cast_to<PackedScene>(i_container->items[index])->instance());
		item->set_global_position(cast_to<Node2D>(item_points[i])->get_global_position());
		get_node("/root/Node2D/Items")->add_child(item, true);
	}
}

void godot::SpawnEnemyController::_register_methods()
{
	register_method("_ready", &SpawnEnemyController::_ready);
	register_method("_prepare_spawn", &SpawnEnemyController::_prepare_spawn);
	register_method("_on_Area2D_area_entered", &SpawnEnemyController::_on_Area2D_area_entered);
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
		String room_type = other->get_parent()->call("_get_type");
		Godot::print(room_type);
		if (room_type == "room") 
		{
			spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
			enemies_count = other->get_parent()->call("_get_enemies_count");
			enemies = other->get_parent()->call("_get_enemies");
		}
		else if (room_type == "boss") 
		{
			SpawnBoss(other->get_parent());
		}
		else if (room_type == "item_room")
		{
			SpawnItems();
		}
		other->queue_free();
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
