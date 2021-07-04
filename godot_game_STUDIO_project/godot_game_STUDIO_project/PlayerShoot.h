#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerShoot : public PlayerData
	{
		std::vector<Node2D*> available_bullets;
		int max_bullet_count;

		Vector2 bullet_dir;
		AnimatedSprite* sprite = nullptr;
		float speed_delta = 2.5;

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
		void _set_controll_buttons(String move_up, String move_down, String move_left, 
			String move_right, String fight_up, String fight_down, String fight_left, String fight_right, String special);
	};
}
