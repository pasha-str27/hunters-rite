#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

AudioController* AudioController::singleton = nullptr;

bool godot::AudioController::_audio_fade_to_main_menu(Timer* timer, Node* node)
{
	timer->disconnect("timeout", node, "_audio_fade_to_main_menu");

	if (audio_server->get_bus_volume_db(2) <= -75
		&& audio_server->get_bus_volume_db(3) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(2) > -75)
		audio_server->set_bus_volume_db(2, audio_server->get_bus_volume_db(2) - 0.8);

	if (audio_server->get_bus_volume_db(3) > -75)
		audio_server->set_bus_volume_db(3, audio_server->get_bus_volume_db(3) - 0.8);

	timer->connect("timeout", node, "_audio_fade_to_main_menu");
	timer->start(0.01);

	return false;
}

bool godot::AudioController::_fade_audio(Timer* timer, Node* node)
{
	timer->disconnect("timeout", node, "_fade_audio");

	if (audio_server->get_bus_volume_db(2) >= MenuButtons::music_audio_level
		&& audio_server->get_bus_volume_db(3) >= MenuButtons::music_audio_level)
		return true;

	if (audio_server->get_bus_volume_db(2) < MenuButtons::music_audio_level)
		audio_server->set_bus_volume_db(2, audio_server->get_bus_volume_db(2) + 0.8);

	if(audio_server->get_bus_volume_db(3) < MenuButtons::music_audio_level)
		audio_server->set_bus_volume_db(3, audio_server->get_bus_volume_db(3) + 0.8);

	timer->connect("timeout", node, "_fade_audio");
	timer->start(0.01);

	return false;
}

bool godot::AudioController::_change_audio_volume(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	timer->disconnect("timeout", node, "_change_audio_volume");

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) - 0.8);


	timer->connect("timeout", node, "_change_audio_volume");
	timer->start(delta_time);

	return false;
}

bool godot::AudioController::_change_audio_volume_camera_controller(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	timer->disconnect("timeout", node, "_change_audio_volume");

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) >= MenuButtons::music_audio_level - 0.4
		&& audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) < MenuButtons::music_audio_level - 0.4)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) + 1.6);

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1,
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) - 0.8);

	timer->connect("timeout", node, "_change_audio_volume");
	timer->start(delta_time);

	return false;
}

bool godot::AudioController::_audio_fade_to_main_menu(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	if (timer->is_connected("timeout", node, "_audio_fade_to_main_menu"))
	{
		timer->disconnect("timeout", node, "_audio_fade_to_main_menu");
	}
	else
	{
		timer->connect("timeout", node, "_audio_fade_to_main_menu");
		timer->start(0.01);
		return false;
	}

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) <= -75
		&& audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) - 1.6);

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1,
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) - 1.6);

	timer->connect("timeout", node, "_audio_fade_to_main_menu");
	timer->start(delta_time);

	return false;
}

bool godot::AudioController::_mute_audio(Timer* timer, Node* node)
{
	timer->disconnect("timeout", node, "_mute_audio");

	if (audio_server->get_bus_volume_db(2) <= -75
		&& audio_server->get_bus_volume_db(3) <= -75)
		return true;

	if (audio_server->get_bus_volume_db(2) > -75)
		audio_server->set_bus_volume_db(2,
			audio_server->get_bus_volume_db(2) - 0.8);

	if (audio_server->get_bus_volume_db(3) > -75)
		audio_server->set_bus_volume_db(3,
			audio_server->get_bus_volume_db(3) - 0.8);

	timer->connect("timeout", node, "_mute_audio");
	timer->start(0.01);
	return false;
}

bool godot::AudioController::_mute_audio_volume(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time)
{
	timer->disconnect("timeout", node, "_mute_audio_volume");

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) <= -75
		&& audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) >= MenuButtons::music_audio_level - 0.4)
		return true;

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) > -75)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()),
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus())) - 0.8);

	if (audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) < MenuButtons::music_audio_level - 0.4)
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1,
			audio_server->get_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1) + 1.6);

	timer->connect("timeout", node, "_mute_audio_volume");
	timer->start(delta_time);

	return false;
}