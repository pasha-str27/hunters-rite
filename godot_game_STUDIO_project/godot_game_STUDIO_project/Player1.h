#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Player1 : public PlayerData
	{
		static Player1* singleton;

	private:
		Player1(Node2D* obj,Ref<PackedScene> bullet=0);
		std::vector<Node2D*> available_bullets;
		int max_bullet_count;

		Vector2 bullet_dir;
		AnimatedSprite* sprite = nullptr;

	public:
		~Player1();
		void _move();
		void _process_input();
		void _fight(Node* node = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _set_enemy(Node* enemy = nullptr);
		void _set_HP(float value);

		static Player1* get_singleton(Node2D* object, Ref<PackedScene>bullet = 0)
		{
			if (singleton == nullptr)
				singleton = new Player1(object, bullet);

			return singleton;
		}

		void _set_speed(float speed);
		void _take_damage(float damage, bool is_spike = false);
		void _revive();
		void _update_health_bar();
		ProgressBar* _get_health_bar();

	};
}
