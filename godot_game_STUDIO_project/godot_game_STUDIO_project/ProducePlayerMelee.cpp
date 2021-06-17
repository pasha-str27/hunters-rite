#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

IPlayer* ProducePlayerMelee::_get_player(Node2D* object, Ref<PackedScene>bullet)
{
    return new PlayerMelee(object, bullet);
}
