#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SlimeShootAI : public SlimeAI
	{
	public:
		SlimeShootAI(Ref<PackedScene>& bullet, Node2D* node_tmp);
		~SlimeShootAI();
		void _fight(Node2D* player1, Node2D* player2);
	};
}