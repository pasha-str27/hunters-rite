#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SillyBoyDiedAI : public EnemyData, public KinematicBody2D
	{
		bool can_move;

		Vector2 dir;
		bool is_cheking;
		float speed;
		float damage = 33;
		bool is_player1_onArea = false;
		bool is_player2_onArea = false;

		bool was_setted = false;

		Vector2 goal = Vector2::ZERO;

	public:
		Vector2 old_pos;
		Vector2 cur_pos;

		SillyBoyDiedAI(Ref<PackedScene>& bullet, Node2D* node);
		~SillyBoyDiedAI();
		void change_can_fight(bool value);
		virtual void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		//void _change_start_parameters();
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
	};
}