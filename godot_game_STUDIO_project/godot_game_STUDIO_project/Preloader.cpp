#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

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

godot::Preloader::Preloader()
{
}

godot::Preloader::~Preloader()
{
}
