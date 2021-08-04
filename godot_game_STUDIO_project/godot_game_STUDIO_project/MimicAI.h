#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class MimicAI: public EnemyData, public Node2D
	{
	private:
		bool can_damage = false;
		float damage = 10;

		bool is_player1_onArea = false;
		bool is_player2_onArea = false;

		bool was_setted = false;

	public:
		MimicAI(Ref<PackedScene>& bullet, Node2D* node);
		~MimicAI();
		void _process(float delta);
		void change_can_fight(bool value);
		void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _set_player(Node2D* player);
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		void _remove_player(Node2D* player);
	};
}


