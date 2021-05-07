#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class Player2 : public PlayerData
	{
		static Player2* singleton;
		Node* current_enemy;

	private:
		Player2(Node2D* obj, Ref<PackedScene> bullet=0);

	public:
		~Player2();
		void _move();
		void _process_input();
		void _fight(Node* node = nullptr);
		void _add_bullet(Node* node = nullptr);
		void _set_enemy(Node* enemy=nullptr);
		void _take_damage(float damage, bool is_spike = false);

		static Player2* get_singleton(Node2D* object, Ref<PackedScene>bullet = 0)
		{
			if (singleton == nullptr)
				singleton = new Player2(object);

			return singleton;
		}

		void _set_speed(float speed);
		void _set_HP(float value);
		void _revive();
	};
}
