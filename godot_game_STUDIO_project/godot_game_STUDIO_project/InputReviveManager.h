#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class InputReviveManager
	{
		Dictionary input_map;
		String current_key;

	public:
		~InputReviveManager();
		void _set_player_buttons(Dictionary input_map);
		void _generate_new_key();
		String _get_current_key();
		String _get_current_value();
	};
}
