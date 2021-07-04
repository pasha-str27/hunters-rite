#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::SlimeEnemiesHolder::_register_methods()
{
	register_method("_get_enemies_list", &SlimeEnemiesHolder::_get_enemies_list);

	register_property<SlimeEnemiesHolder, Array>("enemies_list", &SlimeEnemiesHolder::enemies_list, {});
}

void godot::SlimeEnemiesHolder::_init()
{
}

Array godot::SlimeEnemiesHolder::_get_enemies_list()
{
	return enemies_list;
}

godot::SlimeEnemiesHolder::SlimeEnemiesHolder()
{
	enemies_list = {};
}

godot::SlimeEnemiesHolder::~SlimeEnemiesHolder()
{
	enemies_list.clear();
}
