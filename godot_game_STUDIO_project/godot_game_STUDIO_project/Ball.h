#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
    class Ball : public Area2D
    {
        GODOT_CLASS(Ball, Area2D);

    public:
        static void _register_methods();
        void _init();
        void _ready();
        void _connect(Node* node);
    };
}
