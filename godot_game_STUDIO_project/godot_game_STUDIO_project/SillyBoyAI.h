#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class SillyBoyAI : public EnemyData, public KinematicBody2D
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

		bool is_attacking = false;
		AnimatedSprite* sprite = nullptr;

	public:
		Vector2 old_pos;
		Vector2 cur_pos;

		SillyBoyAI(Ref<PackedScene>& bullet, Node2D* node);
		~SillyBoyAI();
		void _process(float delta);
		void change_can_fight(bool value);
		virtual void change_direction();
		void _change_dir_after_time();
		virtual void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		bool _is_player_near(Node2D* player);
		void _set_speed(float value);
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		void _change_start_parameters();
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
		void _set_direction(Vector2 direction);
		float _find_max_distance(Vector2 dir);
	};
}