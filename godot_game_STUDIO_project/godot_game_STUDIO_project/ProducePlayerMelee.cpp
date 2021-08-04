#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

IPlayer* ProducePlayerMelee::_get_player(Node2D* object, Ref<PackedScene>bullet)
{
    return new PlayerMelee(object, bullet);
}

IPlayer* godot::ProducePlayerMelee::_get_player_died(Node2D* object, Ref<PackedScene> bullet)
{
    return new PlayerMeleeDied(object, bullet);
}

IPlayer* godot::ProducePlayerMelee::_get_player_ghost(Node2D* object, Ref<PackedScene> bullet)
{
    return new PlayerMeleeGhost(object, bullet);
}
