#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class BulletPull;

	class PlayerShoot : public PlayerData
	{
		BulletPull* bullet_pull = nullptr;

		Vector2 bullet_dir;
		AnimatedSprite* sprite = nullptr;
		float speed_delta = 2.5;
		float prev_speed;

		Particles2D* shoot_particles = nullptr;

	public:
		PlayerShoot(Node2D* obj, Ref<PackedScene> bullet = 0);
		~PlayerShoot();
		void _move();
		void _process_input();
		void _fight(Node* node = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _set_HP(float value);
		void _take_damage(float damage, bool is_spike = false);
		void _update_health_bar();
		ProgressBar* _get_health_bar();
		void _stop_animations();
		void _stop_special();
		void _start_special();
	};
}
