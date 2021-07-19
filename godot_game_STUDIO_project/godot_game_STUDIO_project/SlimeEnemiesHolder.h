#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class SlimeEnemiesHolder: public Node
	{
	private:
		GODOT_CLASS(SlimeEnemiesHolder, Node);
		Array enemies_list = {};
	public:
		static void _register_methods();
		void _init();
		Array _get_enemies_list();
		SlimeEnemiesHolder();
		~SlimeEnemiesHolder();
	};
}


