#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class IEnemyAI
	{
	public:
		virtual void _process(float delta) = 0;
		virtual void _add_bullet(Node* bullet=nullptr) = 0;
		virtual void change_can_fight(bool value) = 0;
		virtual void _remove_side(int side) = 0;
		virtual void _change_dir_after_time() = 0;
		virtual void _delete_player1() = 0;
		virtual void _delete_player2() = 0;
		virtual String _get_current_player() = 0;
		virtual void _set_speed(float value) = 0;
		virtual void _set_enemy(Node2D* enemy) = 0;
		virtual void _set_player1(Node2D* player1) = 0;
		virtual void _set_player2(Node2D* player2) = 0;
		virtual Node2D* _get_player1() = 0;
		virtual Node2D* _get_player2() = 0;
		virtual void _change_dir() = 0;
		virtual void _set_is_player1_onArea(bool value) = 0;
		virtual void _set_is_player2_onArea(bool value) = 0;
	};

	class EnemyAIContext
	{
		IEnemyAI* strategy;

	public:
		EnemyAIContext();
		~EnemyAIContext();
		void _set_strategy(IEnemyAI* strategy);
		void _process(float  delta);
		void set_enemy(Node2D* enemy);
		void set_player1(Node2D* player1);
		void set_player2(Node2D* player2);
		Node2D* get_player1();
		Node2D* get_player2();
		void _add_bullet(Node* bullet);
		void change_can_fight(bool value);
		void _delete_player1();
		void _delete_player2();
		void _remove_side(int side);
		void _change_dir_after_time();
		String _get_current_player();
		void _set_speed(float value);
		void _change_dir();
		void _set_is_player1_onArea(bool value);
		void _set_is_player2_onArea(bool value);
	};


	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D);

		EnemyAIContext *ai;
		Timer* timer;
		Timer* timer_change_dir;
		Timer* timer_check_angry;
		Timer* timer_particles = nullptr;

		float HP;
		Ref<PackedScene> bullet;
		bool is_angry;
		bool entered;
		bool died;
		bool can_move = false;

		AnimatedSprite* sp = nullptr;

		Particles2D* spawn_particles = nullptr;
		Ref<PackedScene> death_particles = nullptr;

		float enemy_price=0;

		public:
			static void _register_methods();
			Enemy();
			~Enemy();
			void _init();
			void _ready();
			void _process(float delta);
			void _take_damage(float damage, int player_id = 0);
			void _add_bullet(Node*bullet);
			void _start_timer();
			void _on_timeout();
			void _destroy_enemy();
			void _remove_player1();
			void _remove_player2();
			void _remove_side(int side);
			void _change_dir_after_time();
			void _start_timer_for_dir_change();
			void _on_Area2D_body_entered(Node* node);
			void _set_angry(Node* node);
			void _set_angry_on_code(bool value);
			bool _get_angry();
			void _stop_timer();
			void _change_angry_on_timeout();
			void _set_player1(Node* player);
			void _set_player2(Node* player);
			void _update_health_bar();
			void _change_animation(String, float);
			void _set_current_player(Node* node);
			void _remove_current_player(Node* node);
			void _check_angry();
			void _on_spawn_end();
			void _on_Area2D_body_exited(Node* node);
			float _get_enemy_price();
	};
}