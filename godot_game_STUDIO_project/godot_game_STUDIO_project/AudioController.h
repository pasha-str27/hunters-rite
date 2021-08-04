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
		int effects_bus_index = 0;
		int backmusic_bus_index = 0;
		int backbossmusic_bus_index = 0;

		AudioController()
		{
			audio_server = AudioServer::get_singleton();
			effects_bus_index = audio_server->get_bus_index("AudioEffects");
			backmusic_bus_index = audio_server->get_bus_index("BackMusic");
			backbossmusic_bus_index = audio_server->get_bus_index("BackBossMusic");
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
		void _play_audio_effect(Node* parent_node, String link_to_audio);
		AudioServer* _get_audio_server();
	};
}