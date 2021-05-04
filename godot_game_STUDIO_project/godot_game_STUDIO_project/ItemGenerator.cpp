#include "ItemGenerator.h"

using namespace godot;

void godot::ItemGenerator::_register_methods()
{
	register_method("_ready", &ItemGenerator::_ready);
	register_method("_get_instance", &ItemGenerator::_get_instance);

	register_property<ItemGenerator, int>("Count Enemies to Spawn", &ItemGenerator::count_to_spawn, 15);
}

void godot::ItemGenerator::_init()
{

}

void godot::ItemGenerator::_ready()
{
	current_count = count_to_spawn;
	items_container = CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "ItemsContainer")->call("_get_instance");
}

void godot::ItemGenerator::_dead_enemy(Vector2 enemy_position)
{
	current_count -= 1;
	if (current_count <= 0) {
		RandomNumberGenerator* rng = RandomNumberGenerator::_new();
		rng->randomize();

		int index = rng->randi_range(0, items_container->items.size() - 1);
		rng = nullptr;

		auto item = cast_to<Node2D>(cast_to<PackedScene>(items_container->items[index])->instance());
		item->set_global_position(enemy_position);
		item->set_z_index(1);
		Godot::print("spawned");
		CustomExtensions::GetChildByName(get_node("/root/Node2D"), "Items")->add_child(item);
		current_count = count_to_spawn;
	}
}

ItemGenerator* godot::ItemGenerator::_get_instance()
{
	return this;
}

godot::ItemGenerator::ItemGenerator()
{
}

godot::ItemGenerator::~ItemGenerator()
{
	items_container = nullptr;
}
