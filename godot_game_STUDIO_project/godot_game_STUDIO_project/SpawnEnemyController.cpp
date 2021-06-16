#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SpawnEnemyController::_register_methods()
{
	register_method("_ready", &SpawnEnemyController::_ready);
	register_method("_prepare_spawn", &SpawnEnemyController::_prepare_spawn);
	register_method("_spawn", &SpawnEnemyController::_spawn);
	register_method("_on_Area2D_area_entered", &SpawnEnemyController::_on_Area2D_area_entered);
	register_method("_get_current_level_name", &SpawnEnemyController::_get_current_level_name);
	register_method("_stand_random_level", &SpawnEnemyController::_stand_random_level);

	register_property<SpawnEnemyController, Ref<PackedScene>>("Altar prefab", &SpawnEnemyController::altar, nullptr);
	//register_property<SpawnEnemyController, int>("Levels Count", &SpawnEnemyController::levels_count, 7);
	register_property<SpawnEnemyController, Array>("enemy_list", &SpawnEnemyController::enemy_list_prefabs, {});
}

void godot::SpawnEnemyController::SpawnEnemies()
{
	Enemies* enemies = Enemies::get_singleton();
	if ((String)CameraController::current_room->call("_get_room_type") != "game_room" 
		|| (bool)CameraController::current_room->call("_get_were_here"))
	{
		enemies->set_spawning(false);
		return;
	}

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	////////////////////////////////////////////////////////////////
	//тут генерація мобів
	//float current_value = CameraController::current_room->call("_get_room_difficulty");

	float current_value = 15;
	std::vector<Vector2> taken_positions;

	enemies->set_enemy_to_spawn_count(0);
	enemies->set_spawning(true);

	while (current_value >= min_enemy_price)
	{
		Ref<PackedScene> prefab = enemy_list_prefabs[rng->randi_range(0, enemy_list_prefabs.size() - 1)];
		if ((float)prefab->instance()->call("_get_enemy_price") <= current_value)
		{
			Node2D* enemy = cast_to<Node2D>(prefab->instance());
			CameraController::current_room->add_child(enemy);
			current_value -= (float)prefab->instance()->call("_get_enemy_price");
			int pos_x;
			int pos_y;
			do
			{
				pos_x = rng->randi_range(1, 26);
				pos_y = rng->randi_range(4, 15);
			} while (!(bool)CameraController::current_room->call("_is_empty_pos", pos_y, pos_x));
			
			enemies->set_enemy_to_spawn_count(enemies->get_enemy_to_spawn_count() + 1);

			taken_positions.push_back(Vector2(pos_x, pos_y));

			enemy->set_global_position((Vector2(pos_x, pos_y) * 32
				+ CameraController::current_room->get_global_position()
				- Vector2(896, 544) / 2 + Vector2(16, 16)));

			enemy->get_node(NodePath(prefab->instance()->get_name()))->call("_change_start_parameters");

			CameraController::current_room->call("_set_cell_value", pos_y, pos_x, 7);
		}
	}

	if (enemies->get_enemy_to_spawn_count() == 0)
		enemies->set_spawning(false);

	for(int i=0;i< taken_positions.size();++i)
		CameraController::current_room->call("_set_cell_value", taken_positions[i].y, taken_positions[i].x, 0);

	////////////////////////////////////////////////////////////////



	/*for (int i = 0; i < enemies.size(); i++) 
	{
		if (spawn_points.size() == 0)
			break;

		int rand_point = rng->randi_range(0, (int64_t)spawn_points.size() - 1);

		Vector2 pos = cast_to<Node2D>(spawn_points[rand_point])->get_global_position();

		auto spawned_enemy = cast_to<Node2D>(cast_to<PackedScene>(enemies[i])->instance());
		spawned_enemy->set_global_position(pos);
		get_node("/root/Node2D/Node")->call_deferred("add_child", spawned_enemy);

		spawn_points.remove(rand_point);
	}*/

	rng = nullptr;

	//enemies.clear();
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

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	auto spawned_altar = cast_to<Node2D>(altar->instance());
	spawned_altar->set_global_position(this->get_global_position());

	get_node("/root/Node2D/Node")->add_child(spawned_altar, true);

	for (int i = 0; i < item_points.size(); i++)
	{
		int index = rng->randi_range(0, i_container->items.size() - 1);
		auto item = cast_to<Node2D>(cast_to<PackedScene>(i_container->items[index])->instance());
		item->set_global_position(cast_to<Node2D>(item_points[i])->get_global_position());
		get_node("/root/Node2D/Items")->add_child(item, true);
	}

	rng = nullptr;
}

void godot::SpawnEnemyController::_init()
{
	enemies_count = 5;
}

void godot::SpawnEnemyController::_ready()
{
	min_enemy_price = cast_to<PackedScene>(enemy_list_prefabs[0])->instance()->call("_get_enemy_price");
	for (int i = 1; i < enemy_list_prefabs.size(); ++i)
		if ((float)cast_to<PackedScene>(enemy_list_prefabs[i])->instance()->call("_get_enemy_price") < min_enemy_price)
			min_enemy_price = cast_to<PackedScene>(enemy_list_prefabs[i])->instance()->call("_get_enemy_price");

	add_child(timer);
	//_stand_random_level();
}

void godot::SpawnEnemyController::_prepare_spawn()
{
	if (PlayersContainer::_get_instance()->_get_player1() != nullptr)
		PlayersContainer::_get_instance()->_get_player1()->call("_change_moving", true);

	if (PlayersContainer::_get_instance()->_get_player2() != nullptr)
		PlayersContainer::_get_instance()->_get_player2()->call("_change_moving", true);


	//if (enemies.size() == 0)
	//{
	//	get_parent()->call("_open_doors");
	//	return;
	//}

	timer->connect("timeout", this, "_spawn");
	timer->start(.3f);
}

void godot::SpawnEnemyController::_spawn()
{
	timer->disconnect("timeout", this, "_spawn");

	SpawnEnemies();
}

void godot::SpawnEnemyController::_on_Area2D_area_entered(Node* other)
{
	if (other->is_in_group("room")) 
	{
		String room_type = other->get_parent()->call("_get_type");
		if (room_type == "room") 
		{
			get_parent()->call("_close_doors");
			//spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
			enemies = other->get_parent()->call("_get_enemies");
		}
		else 
			if (room_type == "boss") 
			{
				//spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
				enemies = other->get_parent()->call("_get_enemies");
				get_parent()->call("_close_doors");
				SpawnBoss();
			}
			else 
				if (room_type == "item_room")
				{
					//spawn_points = other->get_parent()->get_node("SpawnPoints")->get_children();
					enemies = other->get_parent()->call("_get_enemies");
					get_parent()->call("_close_doors");
					SpawnItems();
				}

		get_parent()->call("_set_current_room_type", room_type);

		other->queue_free();
		return;
	}
}

void godot::SpawnEnemyController::_stand_random_level()
{
	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();
	int level_number = rng->randi_range(1, levels_count);


	ResourceLoader* resource_loader = ResourceLoader::get_singleton();
	Ref<PackedScene> level = resource_loader->load("res://Assets/Prefabs/Scenes/Levels/Level_" + String::num(level_number) + ".tscn");
	auto spawned_level = cast_to<Node2D>(level->instance());
	get_node("/root/Node2D/Node")->call_deferred("add_child", spawned_level, true);

	current_level = "Level_" + String::num(level_number);
	rng = nullptr;
}

String godot::SpawnEnemyController::_get_current_level_name()
{
	return this->current_level;
}

godot::SpawnEnemyController::SpawnEnemyController()
{
	timer = Timer::_new();
}

godot::SpawnEnemyController::~SpawnEnemyController()
{
	enemies.clear();
	timer = nullptr;
	i_container = nullptr;
}
