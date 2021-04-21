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

	public:
		~Player1();
		void move();
		void process_input();
		void fight();
		void add_bullet(Node* node=nullptr);

		static Player1* get_singleton(Node2D* object, Ref<PackedScene>bullet = 0)
		{
			if (singleton == nullptr)
				singleton = new Player1(object, bullet);

			return singleton;
		}

		void set_speed(float speed);
	};
}
