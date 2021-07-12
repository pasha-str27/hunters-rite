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
	
	register_property<SpawnEnemyController, Ref<PackedScene>>("Altar prefab", &SpawnEnemyController::altar, nullptr);
	register_property<SpawnEnemyController, Array>("enemy_list", &SpawnEnemyController::enemy_list_prefabs, {});
	register_property<SpawnEnemyController, Ref<PackedScene>>("boss_prefab", &SpawnEnemyController::boss_prefab, nullptr);
	register_property<SpawnEnemyController, Ref<PackedScene>>("boss_slime_prefab", &SpawnEnemyController::boss_slime_prefab, nullptr);
	register_property<SpawnEnemyController, Ref<PackedScene>>("spider_prefab", &SpawnEnemyController::spider_prefab, nullptr);
}

void godot::SpawnEnemyController::SpawnEnemies()
{
	Enemies* enemies = Enemies::get_singleton();

	if ((String)CameraController::current_room->call("_get_room_type") == "boss_room"
		&& !(bool)CameraController::current_room->call("_get_were_here"))
	{
		enemies->set_enemy_to_spawn_count(0);
		enemies->set_spawning(true);

		SpawnBoss();
		return;
	}

	if ((String)CameraController::current_room->call("_get_room_type") != "game_room" 
		|| (bool)CameraController::current_room->call("_get_were_here"))
	{
		enemies->set_spawning(false);
		return;
	}

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	float current_value = 50; //_calculate_room_difficulty();
	std::vector<Vector2> taken_positions;

	enemies->set_enemy_to_spawn_count(0);
	enemies->set_spawning(true);

	Array enemy_list = enemy_list_prefabs[CameraController::current_level-1].operator godot::Array();

	float min_enemy_price = _find_min_enemy_price();

	while (current_value >= min_enemy_price)
	{
		Ref<PackedScene> prefab = enemy_list[rng->randi_range(0, enemy_list.size() - 1)];
		if ((float)prefab->instance()->call("_get_enemy_price") <= current_value)
		{
			Node2D* enemy = cast_to<Node2D>(prefab->instance());
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
			CameraController::current_room->call("_add_new_enemy", enemy, (Vector2(pos_x, pos_y) * 32
				+ CameraController::current_room->get_global_position()
				- Vector2(896, 544) / 2 + Vector2(16, 16)));

			CameraController::current_room->call("_set_cell_value", pos_y, pos_x, 7);
		}
	}

	if (enemies->get_enemy_to_spawn_count() == 0)
		enemies->set_spawning(false);

	for(int i=0;i< taken_positions.size();++i)
		CameraController::current_room->call("_set_cell_value", taken_positions[i].y, taken_positions[i].x, 0);
}

void godot::SpawnEnemyController::SpawnBoss()
{
	if (CameraController::current_level == 2)
	{
		_spawn_boss(boss_prefab);

		std::vector<Vector2> taken_positions;

		auto enemies = Enemies::get_singleton();

		enemies->set_spawning(true);

		RandomNumberGenerator* rng = RandomNumberGenerator::_new();
		rng->randomize();

		int spider_count = 2;
		for (int i = 0; i < spider_count; ++i)
		{
			Node2D* enemy = cast_to<Node2D>(spider_prefab->instance());
			int pos_x;
			int pos_y;
			do
			{
				pos_x = rng->randi_range(1, 26);
				pos_y = rng->randi_range(4, 15);
			} while (!(bool)CameraController::current_room->call("_is_empty_pos", pos_y, pos_x));

			enemies->set_enemy_to_spawn_count(enemies->get_enemy_to_spawn_count() + 1);

			taken_positions.push_back(Vector2(pos_x, pos_y));
			CameraController::current_room->call("_add_new_enemy", enemy, (Vector2(pos_x, pos_y) * 32
				+ CameraController::current_room->get_global_position()
				- Vector2(896, 544) / 2 + Vector2(16, 16)));

			CameraController::current_room->call("_set_cell_value", pos_y, pos_x, 7);
		}

		for (int i = 0; i < taken_positions.size(); ++i)
			CameraController::current_room->call("_set_cell_value", taken_positions[i].y, taken_positions[i].x, 0);

		taken_positions.clear();
	}
	else
	{
		if (CameraController::current_level == 5)
			_spawn_boss(boss_slime_prefab);
		else
		{
			if (!CameraController::current_room->has_node("exit"))
			{
				Ref<PackedScene> exit_prefab = nullptr;
				exit_prefab = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/exit.tscn");
				Node2D* exit_node = Node::cast_to<Node2D>(exit_prefab->instance());
				CameraController::current_room->add_child(exit_node, true);
			}
		}
	}
}

void godot::SpawnEnemyController::SpawnItems()
{
	i_container = get_node("/root/Node2D/Node/ItemsContainer")->call("_get_instance");

	Array item_points = get_node("ItemPoints")->get_children();

	Ref<RandomNumberGenerator> rng = RandomNumberGenerator::_new();
	rng->randomize();

	auto spawned_altar = cast_to<Node2D>(altar->instance());
	spawned_altar->set_global_position(this->get_global_position());

	get_node("/root/Node2D/Node/Generation")->add_child(spawned_altar, true);

	for (int i = 0; i < item_points.size(); i++)
	{
		int index = rng->randi_range(0, i_container->items.size() - 1);
		auto item = cast_to<Node2D>(cast_to<PackedScene>(i_container->items[index])->instance());
		item->set_global_position(cast_to<Node2D>(item_points[i])->get_global_position());
		get_node("/root/Node2D/Items")->add_child(item, true);
	}

	rng = nullptr;
}

void godot::SpawnEnemyController::SpawnKey()
{
	auto spawned_pedestal = cast_to<Node2D>(pedestal->instance());
	spawned_pedestal->set_global_position(cast_to<Node2D>(get_parent())->get_global_position());
	get_node("/root/Node2D/Node/Generation")->add_child(spawned_pedestal, true);
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
	if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
		PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1)->call("_change_moving", true);

	if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
		PlayersContainer::_get_instance()->_get_player2_regular()->call("_change_moving", true);

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
				else
					if (room_type == "quest_room")
					{
						SpawnKey();
					}

		get_parent()->call("_set_current_room_type", room_type);

		other->queue_free();
		return;
	}
}

String godot::SpawnEnemyController::_get_current_level_name()
{
	return this->current_level;
}

float godot::SpawnEnemyController::_calculate_room_difficulty()
{
	float PH_k = 1,
		AS1 = 1,
		AS2 = 1,
		DPS_k = 1,
		RFS = 0,
		MK = 0,
		CK = 0,
		K_k = 1,
		PH1 = 0,
		PH2 = 0,
		D1 = 0,
		D2 = 0;

	Node2D* player = PlayersContainer::_get_instance()->_get_player1();
	if (player != nullptr)
	{
		PH1 = player->call("_get_HP");
		D1 = player->call("_get_damage");
	}

	player = PlayersContainer::_get_instance()->_get_player2();
	if (player != nullptr)
	{
		PH2 = player->call("_get_HP");
		D2 = player->call("_get_damage");
	}

	CK = PlayersContainer::_get_instance()->_get_key_list().size();
	MK = get_parent()->get_parent()->get_node("Generation")->call("_get_keys_count");

	player = nullptr;

	return ((PH1 + PH2) * PH_k) / 2 + ((D1 * AS1 + D2 * AS2) / 2) * DPS_k - RFS + (MK - CK) * K_k;
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

float godot::SpawnEnemyController::_find_min_enemy_price()
{
	Array enemy_list = enemy_list_prefabs[CameraController::current_level - 1].operator godot::Array();;
	float min_enemy_price = cast_to<PackedScene>(enemy_list[0])->instance()->call("_get_enemy_price");

	for (int i = 1; i < enemy_list.size(); ++i)
		if ((float)cast_to<PackedScene>(enemy_list[i])->instance()->call("_get_enemy_price") < min_enemy_price)
			min_enemy_price = cast_to<PackedScene>(enemy_list[i])->instance()->call("_get_enemy_price");
	
	return min_enemy_price;
}

void godot::SpawnEnemyController::_spawn_boss(Ref<PackedScene> boss_prefab)
{
	get_parent()->call("_start_mute_volume");
	Enemies::get_singleton()->set_enemy_to_spawn_count(1);
	auto boss = cast_to<Node2D>(boss_prefab->instance());
	boss->set_global_position(cast_to<Node2D>(get_parent())->get_global_position());
	get_node("/root/Node2D/Node")->add_child(boss, true);

	if (boss->has_method("_change_start_parameters"))
	{
		boss->call("_change_start_parameters");
		return;
	}

	for (int i = 0; i < boss->get_child_count(); ++i)
		if (boss->get_child(i)->has_method("_change_start_parameters"))
		{
			boss->get_child(i)->call("_change_start_parameters");
			return;
		}
}