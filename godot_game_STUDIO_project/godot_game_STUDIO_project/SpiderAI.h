#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BulletPull;

	class SpiderAI : public EnemyData, public KinematicBody2D
	{
		int max_bullet_count;
		BulletPull* bullet_pull = nullptr;
		bool can_move;

		Vector2 dir;
		bool is_cheking;
		float speed;
		Vector2 old_pos;
		Vector2 cur_pos;
		Vector2 goal;

	public:
		SpiderAI(Ref<PackedScene>& bullet, Node2D* node);
		~SpiderAI();
		void _process(float delta);
		void _add_bullet(Node* node = nullptr);
		void change_can_fight(bool value);
		void change_direction();
		void _change_dir_after_time();
		void _fight(Node2D *player1, Node2D* player2);
		void _set_speed(float value);
		void _change_start_parameters();
		bool _is_player_near(Node2D* player);
	};
}
