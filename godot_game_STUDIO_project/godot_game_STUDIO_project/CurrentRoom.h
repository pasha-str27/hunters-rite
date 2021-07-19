#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class CurrentRoom
	{
		static CurrentRoom* curr_room;
		Node2D* cur_room_node = nullptr;

		CurrentRoom() {};

	public:
		static CurrentRoom* get_singleton()
		{
			if (curr_room == nullptr)
				curr_room = new CurrentRoom;
			return curr_room;
		}

		void _set_current_room(Node2D* room);
		Node2D* _get_current_room();
	};
}
