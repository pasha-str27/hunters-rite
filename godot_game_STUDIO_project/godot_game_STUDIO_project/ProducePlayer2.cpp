#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

IPlayer* ProducePlayer2::_get_player(Node2D* object, Ref<PackedScene>bullet)
{
    return new Player2(object, bullet);
}
