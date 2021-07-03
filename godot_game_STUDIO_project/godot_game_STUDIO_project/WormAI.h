#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class WormAI: public EnemyData, public KinematicBody2D
	{
	private:
		bool can_move;
		bool finished_hide_anim = false;
		bool is_hided = false;
		bool shooted = false;
		bool prepare_to_shoot = false;
		float damage = 33;

		int max_bullet_count = 10;
		std::vector<Node2D*> available_bullets;

		AnimatedSprite* ground_front = nullptr;
		AnimatedSprite* ground_back = nullptr;

		Vector2 target = Vector2::ZERO;
		Array free_cells = {};

	public:
		WormAI(Ref<PackedScene>& bullet, Node2D* node);
		~WormAI();
		void _process(float delta);
		void _set_speed(float value);
		void change_can_fight(bool value);
		void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
		void _set_target();
		void _set_next_pos();
		void _enable_collisions();
		void _disable_collisions();
	};
}

