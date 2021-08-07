#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SillyBoyDiedAI : public EnemyData, public KinematicBody2D
	{
		float damage = 33;
		bool is_player1_onArea = false;
		bool is_player2_onArea = false;

		bool was_setted = false;
	public:

		SillyBoyDiedAI(Ref<PackedScene>& bullet, Node2D* node);
		~SillyBoyDiedAI();
		virtual void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
	};
}