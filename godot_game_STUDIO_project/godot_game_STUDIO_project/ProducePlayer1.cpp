#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

using namespace godot;

IPlayer* ProducePlayer1::_get_player(Node2D* object, Ref<PackedScene>bullet)
{
    return Player1::get_singleton(object, bullet);
}
