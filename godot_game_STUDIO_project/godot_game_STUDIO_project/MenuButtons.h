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
		Ref<PackedScene> authors_scene;
		Ref<PackedScene> items_scene;
		Ref<PackedScene> game_scene;
		Ref<PackedScene> fade;
		Ref<PackedScene> fade_in;

		static bool was_focused;
		static bool is_full_screen;
		static float effect_audio_level;

		Timer* timer_music;
		Timer* timer_music_out;
		Timer* timer;
		float delta_time;
		static AudioStreamPlayer2D* audio;
		float delta_step;

	public:
		MenuButtons();
		~MenuButtons();

		int click_counter;
		static float music_audio_level;
		static bool was_loaded;
		bool was_quit_focused;	

		static void _register_methods();
		void _init();
		void _ready();

		void _on_Play_pressed(Variant body);
		void _on_Option_pressed(Variant body);
		void _on_Quit_pressed(Variant body);
		void _on_Back_pressed(Variant body);
		void _on_Flower_pressed(Variant body);
		void _on_Items_pressed(Variant body);
		void _on_FullScreen_pressed(Variant body);
		void _play_effect();
		void _play_change_cursor_effect();
		void _on_Quit_focus_entered();
		void _on_Flower_button_focus_entered();
		void _on_Flower_button_focus_exited();
		void _on_Slime_button_focus_entered();
		void _on_Slime_button_focus_exited();
		void _on_Coming_soon_button_focus_entered();
		void _on_Coming_soon_button_focus_exited();
		void _on_animated_focus_entered(String button_name, String animated_name);
		void _on_animated_focus_exited(String button_name, String animated_name);
		void _set_animated_focus(String button_name,String animated_name,bool mode);
		void _on_Quit_focus_exited();
		void _on_effects_value_changed(float value);
		void _on_music_value_changed(float value);
		void save_game();
		void load_game();
		void _timeout();
		void _change_audio_volume();
		void _on_Resume_pressed(Input* event);
		void _on_Menu_pressed(Input* event);
		void _on_Retry_pressed(Variant body);
		void _move_to_main_menu();
		void _audio_fade_to_main_menu();
		void _fade_audio();
		void _input(Input* event);
		void _reload_scene();
	};
}