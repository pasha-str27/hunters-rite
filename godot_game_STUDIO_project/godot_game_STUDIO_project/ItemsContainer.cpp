#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::ItemsContainer::_register_methods()
{
	register_method("_ready", &ItemsContainer::_ready);
	register_method("_get_instance", &ItemsContainer::_get_instance);
	register_method("_spawn_random_item", &ItemsContainer::_spawn_random_item);
	
	register_property<ItemsContainer, Array>("Items", &ItemsContainer::items, {});
}

void godot::ItemsContainer::_init()
{
}

void godot::ItemsContainer::_ready()
{
}

ItemsContainer* godot::ItemsContainer::_get_instance()
{
	return this;
}

void godot::ItemsContainer::_spawn_random_item(Vector2 pos)
{
	RandomNumberGenerator* rng = RandomNumberGenerator::_new();
	rng->randomize();
	int64_t rand_index = rng->randi_range(0, (int64_t)items.size() - 1);
	auto item = cast_to<Node2D>(cast_to<PackedScene>(items[rand_index])->instance());
	item->set_global_position(pos);
	get_node("/root/Node2D/Items")->add_child(item);
}

godot::ItemsContainer::ItemsContainer()
{
}

godot::ItemsContainer::~ItemsContainer()
{
	items = {};
}
