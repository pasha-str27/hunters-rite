#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot {
	class LocaledLabel: public Label
	{
	private:
		GODOT_CLASS(LocaledLabel, Label);
		String text_key;
	public:
		static void _register_methods();
		void _init();
		void _ready();
		LocaledLabel();
		~LocaledLabel();
	};
}


