#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class IEnemyAI;
	class EnemyAIContext;
	class ResourceContainer;

	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D);

		EnemyAIContext *ai;
		Timer* timer;
		Timer* timer_change_dir;
		Timer* timer_check_angry;
		Timer* timer_particles = nullptr;

		float HP;
		float max_HP;
		Ref<PackedScene> bullet;
		bool is_angry;
		bool entered;
		bool died;
		bool can_move = false;
		bool was_died = false;
		float time_to_revive = 5;

		AnimatedSprite* sp = nullptr;

		Particles2D* spawn_particles = nullptr;
		Ref<PackedScene> death_particles = nullptr;
		ProgressBar* health_bar;

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
			void _start_fixed_timer(float time);
			void _on_fixed_timeout();
			void _destroy_enemy();
			void _remove_player1();
			void _remove_player2();
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
			void _change_start_parameters();
			void _remove_taken_positions();
			void _set_direction(Node* player, Vector2 direction);
			void _revive();
			void _on_Area2D_body_entered_player_fight(Node* node);
	};
}