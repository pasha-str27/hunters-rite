#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BulletPull;

	class SlimeShootAI : public SlimeAI
	{
		BulletPull* bullet_pull = nullptr;
		Node2D* first_player = nullptr;
		Node2D* second_player = nullptr;
	public:
		SlimeShootAI(Ref<PackedScene>& bullet, Node2D* node_tmp);
		~SlimeShootAI();
		void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* node = nullptr);
		void change_direction();
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
	};
}