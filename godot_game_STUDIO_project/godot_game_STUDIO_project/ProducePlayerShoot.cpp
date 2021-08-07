#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

IPlayer* ProducePlayerShoot::_get_player(Node2D* object, Ref<PackedScene> bullet)
{
    return new PlayerShoot(object, bullet);
}

IPlayer* godot::ProducePlayerShoot::_get_player_died(Node2D* object, Ref<PackedScene> bullet)
{
    return new PlayerShootDied(object, bullet);
}

IPlayer* godot::ProducePlayerShoot::_get_player_ghost(Node2D* object, Ref<PackedScene> bullet)
{
    return new PlayerShootGhost(object, bullet);
}
