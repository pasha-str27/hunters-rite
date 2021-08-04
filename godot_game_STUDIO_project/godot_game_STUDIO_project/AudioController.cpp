#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

AudioController* AudioController::singleton = nullptr;

bool godot::AudioController::_audio_fade_to_main_menu(Timer* timer, Node* node)
{
	if (audio_server->get_bus_volume_db(backmusic_bus_index) <= -75
		&& audio_server->get_bus_volume_db(backbossmusic_bus_index) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(backmusic_bus_index) > -75)
		audio_server->set_bus_volume_db(backmusic_bus_index, audio_server->get_bus_volume_db(2) - 0.8);

	if (audio_server->get_bus_volume_db(backbossmusic_bus_index) > -75)
		audio_server->set_bus_volume_db(backbossmusic_bus_index, audio_server->get_bus_volume_db(backbossmusic_bus_index) - 0.8);

	return false;
}

bool godot::AudioController::_fade_audio(Timer* timer, Node* node)
{
	if (audio_server->get_bus_volume_db(backmusic_bus_index) >= MenuButtons::music_audio_level
		&& audio_server->get_bus_volume_db(backbossmusic_bus_index) >= MenuButtons::music_audio_level)
		return true;

	if (audio_server->get_bus_volume_db(backmusic_bus_index) < MenuButtons::music_audio_level)
		audio_server->set_bus_volume_db(backmusic_bus_index, audio_server->get_bus_volume_db(backmusic_bus_index) + 0.8);

	if(audio_server->get_bus_volume_db(backbossmusic_bus_index) < MenuButtons::music_audio_level)
		audio_server->set_bus_volume_db(backbossmusic_bus_index, audio_server->get_bus_volume_db(backbossmusic_bus_index) + 0.8);

	return false;
}

bool godot::AudioController::_change_audio_volume(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) - 0.8);

	return false;
}

bool godot::AudioController::_change_audio_volume_camera_controller(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) >= MenuButtons::music_audio_level - 0.4
		&& audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) < MenuButtons::music_audio_level - 0.4)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) + 1.6);

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1,
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) - 0.8);

	return false;
}

bool godot::AudioController::_audio_fade_to_main_menu(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) <= -75
		&& audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) - 1.6);

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1,
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) - 1.6);

	return false;
}

bool godot::AudioController::_mute_audio(Timer* timer, Node* node)
{
	if (audio_server->get_bus_volume_db(backmusic_bus_index) <= -75
		&& audio_server->get_bus_volume_db(backbossmusic_bus_index) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(backmusic_bus_index) > -75)
		audio_server->set_bus_volume_db(backmusic_bus_index,
			audio_server->get_bus_volume_db(backmusic_bus_index) - 0.8);

	if (audio_server->get_bus_volume_db(backbossmusic_bus_index) > -75)
		audio_server->set_bus_volume_db(backbossmusic_bus_index,
			audio_server->get_bus_volume_db(backbossmusic_bus_index) - 0.8);

	return false;
}

void godot::AudioController::_play_audio_effect(Node* parent_node, String link_to_audio)
{
	Ref<PackedScene> prefab = nullptr;
	prefab = ResourceLoader::get_singleton()->load(link_to_audio);
	parent_node->add_child(prefab->instance());
}

AudioServer* godot::AudioController::_get_audio_server()
{
	return audio_server;
}

bool godot::AudioController::_mute_audio_volume(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) <= -75
		&& audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) >= MenuButtons::music_audio_level - 0.4)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) - 0.8);

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) < MenuButtons::music_audio_level - 0.4)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1,
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) + 1.6);

	return false;
}