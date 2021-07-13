#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif
namespace godot {
	class NagaAI: public EnemyData, public KinematicBody2D
	{
	private:
		bool can_move = false;
		float speed = 100;
		float damage = 50;
		bool is_angry = false;
		bool is_disappearing = false;
		bool can_attack = true;
		bool is_teleported = false;

		bool is_player1_onArea = false;
		bool is_player2_onArea = false;

		Array free_cells = {};
		Node2D* target = nullptr;

		AnimatedSprite* sprite = nullptr;

		Particles2D* vampirism_particles = nullptr;

	public:
		NagaAI(Ref<PackedScene>& bullet, Node2D* node);
		~NagaAI();
		void _process(float delta);
		void change_can_fight(bool value);
		void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _remove_player(Node2D* player);
		void _set_target();
		void _set_next_pos();
		void _enable_collisions();
		void _disable_collisions();
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
		void _set_player(Node2D* player);
		void _follow_target(float delta);
		void _take_damage(float damage);
		void _teleport_to_target();
		bool _is_player_near();
		void _make_vampirism();
	};
}

