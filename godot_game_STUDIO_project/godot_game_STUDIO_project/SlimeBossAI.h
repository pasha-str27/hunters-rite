#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{	
	class ISlimeAttackState;
	class BulletPull;

	class SlimeBossAI: public EnemyData, public KinematicBody2D
	{
	private:
		bool can_move;
		float damage = 33;
		float speed = 200;
		bool is_jumping = false;
		bool jumping_up = false;
		int taken_damage = 0;

		int max_bullet_count = 20;
		BulletPull* bullet_pull = nullptr;

		ISlimeAttackState* _attack_state = nullptr;
	
		Vector2 goal = Vector2::ZERO;
		Vector2 target_player = Vector2::ZERO;
		Vector2 empty_pos = Vector2(-99999, -99999);

		Node2D* jump_zone = nullptr;

		Array enemies_to_spawn = {};
		Array places_to_spawn = {};

		Node* camera_shake = nullptr;

	public:
		SlimeBossAI(Ref<PackedScene>& bullet, Node2D* node);
		~SlimeBossAI();
		void _process(float delta);
		void _set_speed(float value);
		void change_can_fight(bool value);
		void _fight(Node2D* player1 = nullptr, Node2D* player2 = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _set_player(Node2D* player);
		void _remove_player(Node2D* player);
		void _change_state(ISlimeAttackState* state);
		void change_can_fight(bool value, ISlimeAttackState* state);
		void _wait(float time);
		void _shoot();
		void _spawn_enemy();
		void _jump();
		void _jumping(float delta);
		void _show_jump_zone();
		void _start_falling();
		void _set_target();
		void _disable_collisions();
		void _enable_collisions();
		void _take_damage(float damage);
		void _make_action_sound();
	};
}