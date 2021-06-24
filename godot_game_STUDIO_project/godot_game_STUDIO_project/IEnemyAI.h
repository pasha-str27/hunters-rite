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
		virtual void _add_bullet(Node* bullet = nullptr) = 0;
		virtual void change_can_fight(bool value) = 0;
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
		virtual void _change_start_parameters() = 0;
		virtual void _set_player(Node2D* player) = 0;
		virtual void _remove_player(Node2D* player) = 0;
	};
}