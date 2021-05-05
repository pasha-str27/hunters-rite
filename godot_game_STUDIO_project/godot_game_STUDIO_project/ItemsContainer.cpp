#include "ItemsContainer.h"

using namespace godot;

void godot::ItemsContainer::_register_methods()
{
	register_method("_ready", &ItemsContainer::_ready);
	register_method("_get_instance", &ItemsContainer::_get_instance);

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

godot::ItemsContainer::ItemsContainer()
{
}

godot::ItemsContainer::~ItemsContainer()
{
	items = {};
}
