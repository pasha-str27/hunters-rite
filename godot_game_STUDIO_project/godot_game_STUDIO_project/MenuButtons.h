#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class MenuButtons : public TextureRect 
	{
		GODOT_CLASS(MenuButtons, TextureRect)

		Ref<PackedScene> click_effect;
		Ref<PackedScene> menu_back;
		Ref<PackedScene> menu_scene;
		Ref<PackedScene> option_scene;
		Ref<PackedScene> notice_scene;
		Ref<PackedScene> game_scene;
		static bool was_focused;

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
		void _play_effect();
		void _play_change_cursor_effect();
		void _on_effects_value_changed(float value);
		void _on_music_value_changed(float value);
		void save_game();
		String save();
		void load_game();
	};
}