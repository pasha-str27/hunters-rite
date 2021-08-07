#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
    class EnemyPrice : public Node2D
    {
        GODOT_CLASS(EnemyPrice, Node2D);
        float enemy_price;

    public:
        static void _register_methods();
        void _init();
        float _get_enemy_price();
    };
}