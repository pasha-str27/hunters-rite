#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class InputReviveManager
	{
		std::vector<String> keys;
		String current_key;

	public:
		~InputReviveManager();
		void _set_player1_buttons();
		void _set_player2_buttons();
		void _generate_new_key();
		String _get_current_key();
	};
}
