#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

IPlayer* ProducePlayerShoot::_get_player(Node2D* object, Ref<PackedScene>bullet)
{
    return new PlayerShoot(object, bullet);
}
