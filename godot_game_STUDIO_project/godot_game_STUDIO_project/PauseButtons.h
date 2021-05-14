#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class PauseButtons : public TextureRect
	{
		GODOT_CLASS(PauseButtons, TextureRect)
		Ref<PackedScene> menu_scene;

	public:
		PauseButtons();
		~PauseButtons();

		static void _register_methods();
		void _init();
		void _ready();
		void _input(Variant event);


		void _on_Resume_pressed(Variant body);
		void _on_Menu_pressed(Variant body);
		void _on_Quit_pressed(Variant body);

	};
}