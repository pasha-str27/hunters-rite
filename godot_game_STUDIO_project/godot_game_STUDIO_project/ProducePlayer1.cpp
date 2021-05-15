#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

IPlayer* ProducePlayer1::_get_player(Node2D* object, Ref<PackedScene>bullet)
{
    return new Player1(object, bullet);
}
