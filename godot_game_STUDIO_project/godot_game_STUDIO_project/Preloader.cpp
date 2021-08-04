#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

#include <TranslationServer.hpp>

void godot::Preloader::_register_methods()
{
	register_method("_ready", &Preloader::_ready);
	register_method("_load_menu", &Preloader::_load_menu);
	register_method("_play_logo_sound", &Preloader::_play_logo_sound);
	register_method("_play_sound", &Preloader::_play_sound);
	register_method("_stop_sounds", &Preloader::_stop_sounds);
}

void godot::Preloader::_init()
{
}

void godot::Preloader::_ready()
{
	load();
	ResourceLoader* resource_loader = ResourceLoader::get_singleton();
	menu_scene = resource_loader->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	cast_to<AnimationPlayer>(get_node("AnimationPlayer"))->play("logo");
	audio = cast_to<AudioStreamPlayer2D>(get_node("LogoSound"));
}

void godot::Preloader::_load_menu()
{
	SceneTree* tree = get_tree();
	get_node("/root")->add_child(menu_scene->instance());
	queue_free();
}

void godot::Preloader::_play_logo_sound()
{
	audio->play();
}

void godot::Preloader::_play_sound(Ref<AudioStream> stream)
{
	_stop_sounds();
	audio->set_stream(stream);
	audio->play();
}

void godot::Preloader::_stop_sounds()
{
	audio->stop();
}

void godot::Preloader::load()
{
	Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);

	auto save_game = File::_new();
	if (!save_game->file_exists("user://savegame_hunters.save"))
		return;

	save_game->open("user://savegame_hunters.save", File::READ);
	Dictionary node_data = JSON::get_singleton()->parse(save_game->get_line())->get_result();

	MenuButtons::is_full_screen = node_data["full_screen"];
	MenuButtons::music_audio_level = node_data["music_level"];
	MenuButtons::effect_audio_level = node_data["effect_level"];
	
	TranslationServer::get_singleton()->set_locale(node_data["locale"]);

	OS::get_singleton()->set_window_fullscreen(MenuButtons::is_full_screen);
	AudioServer::get_singleton()->set_bus_volume_db(1, MenuButtons::effect_audio_level);

	if (!MenuButtons::was_loaded)
	{
		AudioServer::get_singleton()->set_bus_volume_db(2, -80);
		AudioServer::get_singleton()->set_bus_volume_db(3, -80);
	}

	save_game->close();
}

godot::Preloader::Preloader()
{
}

godot::Preloader::~Preloader()
{
	audio = nullptr;
}
