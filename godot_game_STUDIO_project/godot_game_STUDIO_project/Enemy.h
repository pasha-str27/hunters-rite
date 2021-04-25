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
	};


	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D);

		EnemyAIContext *ai;

		float HP;

		public:
			static void _register_methods();
			Enemy();
			~Enemy();
			void _init();
			void _ready();
			void _process(float delta);
			void _take_damage(float damage);
	};
}