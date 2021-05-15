#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SpawnEnemyController::SpawnEnemies()
{
	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();
	
	for (int i = 0; i < enemies.size(); i++) 
	{
		int rand_point = rng->randi_range(0, (int64_t)spawn_points.size() - 1);
		auto spawned_enemy = cast_to<Node2D>(cast_to<PackedScene>(enemies[i])->instance());
		spawned_enemy->set_global_position(cast_to<Node2D>(spawn_points[rand_point])->get_global_position());
		get_node("/root/Node2D/Node")->call_deferred("add_child", spawned_enemy);
	}

	rng = nullptr;

	enemies.clear();
}

void godot::SpawnEnemyController::SpawnBoss()
{
	get_parent()->call("_start_mute_volume");
	auto boss = cast_to<Node2D>(cast_to<PackedScene>(enemies[0])->instance());
	boss->set_global_position(cast_to<Node2D>(get_parent())->get_global_position());
	get_node("/root/Node2D/Node")->add_child(boss, true);
	enemies.pop_front();
}

void godot::SpawnEnemyController::SpawnItems()
{
	i_container = get_node("/root/Node2D/Node/ItemsContainer")->call("_get_instance");

	Array item_points = get_node("ItemPoints")->get_children();

	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();

	auto spawned_altar = cast_to<Node2D>(altar->instance());
	spawned_altar->set_global_position(this->get_global_position());

	get_node("/root/Node2D/Node")->add_child(spawned_altar, true);

	for (int i = 0; i < item_points.size(); i++) {
		int index = rng->randi_range(0, i_container->items.size() - 1);
		auto item = cast_to<Node2D>(cast_to<PackedScene>(i_container->items[index])->instance());
		item->set_global_position(cast_to<Node2D>(item_points[i])->get_global_position());
		get_node("/root/Node2D/Items")->add_child(item, true);
	}
	rng = nullptr;
}

void godot::SpawnEnemyController::_register_methods()
{
	register_method("_ready", &SpawnEnemyController::_ready);
	register_method("_prepare_spawn", &SpawnEnemyController::_prepare_spawn);
	register_method("_spawn", &SpawnEnemyController::_spawn);
	register_method("_on_Area2D_area_entered", &SpawnEnemyController::_on_Area2D_area_entered);
	

	register_property<SpawnEnemyController, Ref<PackedScene>>("Altar prefab", &SpawnEnemyController::altar, nullptr);
}

void godot::SpawnEnemyController::_init()
{
	enemies_count = 5;
}

void godot::SpawnEnemyController::_ready()
{
	add_child(timer);
}

void godot::SpawnEnemyController::_prepare_spawn()
{
	if (spawn_points.size() == 0 || enemies.size() == 0)
	{
		get_parent()->call("_open_doors");
		return;
	}

	timer->connect("timeout", this, "_spawn");
	timer->start(.5f);
}

void godot::SpawnEnemyController::_spawn()
{
	timer->disconnect("timeout", this, "_spawn");

	SpawnEnemies();

	if (Enemies::get_singleton()->_get_enemies_count() > 0)
		get_parent()->call("_close_doors");

	spawn_points.clear();
}

void godot::SpawnEnemyController::_on_Area2D_area_entered(Node* other)
{
	if (other->is_in_group("room")) 
	{
		String room_type = other->get_parent()->call("_get_type");
		if (room_type == "room") 
		{
			get_parent()->call("_close_doors");
			spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
			enemies = other->get_parent()->call("_get_enemies");
		}
		else if (room_type == "boss") 
		{
			spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
			enemies = other->get_parent()->call("_get_enemies");
			get_parent()->call("_close_doors");
			SpawnBoss();
			_prepare_spawn();
		}
		else if (room_type == "item_room")
		{
			SpawnItems();
		}

		other->queue_free();
		return;
	}
}

godot::SpawnEnemyController::SpawnEnemyController()
{
	timer = Timer::_new();
}

godot::SpawnEnemyController::~SpawnEnemyController()
{
	enemies = {};
	spawn_points = {};
	timer = nullptr;
}
