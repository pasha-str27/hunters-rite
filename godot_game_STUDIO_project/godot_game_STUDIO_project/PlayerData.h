#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PlayerData : public IPlayer, public KinematicBody2D
	{
		int speed;
		Vector2 dir;
		Node2D* object;
		bool can_fight_value;

	public:
		PlayerData(Node2D* object, Ref<PackedScene>bullet = 0);
		PlayerData();
		~PlayerData();
		
		virtual void _move();
		virtual void _set_speed(float speed);
		virtual void _fight(Node* node = nullptr) = 0;
		virtual void _add_bullet(Node* node=nullptr) = 0;
		float _get_speed();
		void _set_dir(Vector2 dir);
		Vector2 _get_dir();
		Node2D* _get_object();

		virtual void _process_input() = 0;
		virtual void _change_can_fight(bool value);
		virtual bool _can_fight();
		virtual void _set_enemy(Node* enemy = nullptr)=0;

		static Input* input_controller;
	};
}