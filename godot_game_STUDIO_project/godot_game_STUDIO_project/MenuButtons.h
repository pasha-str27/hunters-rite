#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class MenuButtons : public TextureRect {
		GODOT_CLASS(MenuButtons, TextureRect)
	
	private:
	public:
		MenuButtons();
		~MenuButtons();

		static void _register_methods();
		void _init();
		void _ready();
		
		void _on_Play_pressed(Variant body);
		void _on_Option_pressed(Variant body);
		void _on_Quit_pressed(Variant body);
		void _on_Back_pressed(Variant body);
		void _on_Flower_pressed(Variant body);
		void _on_FullScreen_pressed(Variant body);
	};
}