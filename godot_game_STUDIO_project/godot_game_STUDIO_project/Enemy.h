#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{

	class IEnemyAI
	{
	public:
		virtual void _process(float delta, Node2D* enemy = nullptr, Node2D* player1 = nullptr, Node2D* player2 = nullptr) = 0;
		virtual void _add_bullet(Node* bullet=nullptr) = 0;
		virtual void change_can_fight(bool value) = 0;
		virtual void _remove_side(int side) = 0;
		virtual void _change_dir_after_time() = 0;
		virtual void _delete_player1(Node2D* player1 = nullptr, Node2D* player2 = nullptr) = 0;
		virtual void _delete_player2(Node2D* player1 = nullptr, Node2D* player2 = nullptr) = 0;
		virtual String _get_current_player() = 0;
		virtual void _set_speed(float value) = 0;
	};

	class EnemyAIContext
	{
		IEnemyAI* strategy;

		Node2D* enemy;
		Node2D* player1;
		Node2D* player2;

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
	};


	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D);

		EnemyAIContext *ai;
		Timer* timer;
		Timer* timer_change_dir;

		float HP;
		Ref<PackedScene> bullet;
		bool is_angry;
		bool entered;

		public:
			static void _register_methods();
			Enemy();
			~Enemy();
			void _init();
			void _ready();
			void _process(float delta);
			void _take_damage(float damage);
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
			void _update_health_bar();
	};
}