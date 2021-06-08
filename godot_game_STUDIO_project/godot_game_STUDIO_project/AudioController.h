#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class AudioController
	{
		static AudioController* singleton;
		AudioServer* audio_server = nullptr;

		AudioController()
		{
			audio_server= AudioServer::get_singleton();
		}
	public:
		static AudioController* get_singleton()
		{
			if (singleton == nullptr)
				singleton = new AudioController;

			return singleton;
		}
		
		bool _audio_fade_to_main_menu(Timer* timer, Node* node);
		bool _fade_audio(Timer* timer, Node* node);
		bool _change_audio_volume(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time);
		bool _change_audio_volume_camera_controller(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time);
		bool _mute_audio_volume(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time);
		bool _audio_fade_to_main_menu(Timer* timer, Node* node, AudioStreamPlayer2D* audio, float delta_time);
		bool _mute_audio(Timer* timer, Node* node);
	};
}