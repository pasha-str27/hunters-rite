#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::CameraController::_move(String dir)
{
	auto fade = cast_to<Node2D>(fadeIn->instance());
	//fade->set_global_position(this->get_global_position());
	add_child(fade);

	float vertical_offset = 450;
	float horizontal_offset = 320;
	if (dir == "top")
	{
		float delta = 720;

		set_global_position(get_global_position() - Vector2(0, delta));

		player1->set_global_position(player1->get_global_position() - Vector2(0, vertical_offset));
		player2->set_global_position(player2->get_global_position() - Vector2(0, vertical_offset));
	}

	if (dir == "bottom")
	{
		float delta = 720;

		set_global_position(get_global_position() + Vector2(0, delta));

		player1->set_global_position(player1->get_global_position() + Vector2(0, vertical_offset));
		player2->set_global_position(player2->get_global_position() + Vector2(0, vertical_offset));
	}

	if (dir == "left")
	{
		float delta = 1024;

		set_global_position(get_global_position() - Vector2(delta, 0));

		player1->set_global_position(player1->get_global_position() - Vector2(horizontal_offset, 0));
		player2->set_global_position(player2->get_global_position() - Vector2(horizontal_offset, 0));
	}

	if (dir == "right")
	{
		float delta = 1024;

		set_global_position(get_global_position() + Vector2(delta, 0));

		player1->set_global_position(player1->get_global_position() + Vector2(horizontal_offset, 0));
		player2->set_global_position(player2->get_global_position() + Vector2(horizontal_offset, 0));
	}
}

String godot::CameraController::_get_dir_on_index(int i)
{
	if (i == 0)
		return "left";
	if (i == 1)
		return "right";
	if (i == 2)
		return "top";
	if (i == 3)
		return "bottom";
}

void godot::CameraController::_register_methods()
{
	register_method("_process", &CameraController::_process);
	register_method("_init", &CameraController::_init);
	register_method("_ready", &CameraController::_ready);
	register_method("_door_collision", &CameraController::_door_collision);
	register_method("_close_doors", &CameraController::_close_doors);
	register_method("_open_doors", &CameraController::_open_doors);
	register_method("_start_move", &CameraController::_start_move);
	register_method("_change_audio_volume", &CameraController::_change_audio_volume);

	register_property<CameraController, Ref<PackedScene>>("Fade In Animation", &CameraController::fadeIn, nullptr);
	register_property<CameraController, Ref<PackedScene>>("Fade Out Animation", &CameraController::fadeOut, nullptr);
	register_property<CameraController, Ref<PackedScene>>("game_back_music", &CameraController::game_back, nullptr);
}

void godot::CameraController::_init()
{
	for (int i = 0; i < 4; i++)
		dirs.push_back(0);
}

void godot::CameraController::_ready()
{
	_set_current(true);
	player1 = cast_to<Node2D>(get_node("/root/Node2D/Node/Player1"));
	player2 = cast_to<Node2D>(get_node("/root/Node2D/Node/Player2"));

	if (find_parent("root") != nullptr && !find_parent("root")->has_node("MenuGameMusic"))
	{
		audio = cast_to<AudioStreamPlayer2D>(game_back->instance());
		find_parent("root")->call_deferred("add_child", audio);
	}

	timer_audio = Timer::_new();
	add_child(timer_audio);
	timer_audio->connect("timeout", this, "_change_audio_volume");
	timer_audio->start(time_delta);
}

void godot::CameraController::_process()
{
}

void godot::CameraController::_door_collision(String door_dir)
{
	int index = 0;
	if (door_dir.find("left") != -1)
		index = 0;
	if (door_dir.find("right") != -1)
		index = 1;
	if (door_dir.find("top") != -1)
		index = 2;
	if (door_dir.find("bottom") != -1)
		index = 3;

	if (door_dir[0] == '-')
	{
		dirs[index] = (int)dirs[index] - 1;
		return;
	}
	dirs[index] = (int)dirs[index] + 1;

	if ((int)dirs[index] == 2 && is_open_door) 
	{
		auto fade = cast_to<Node2D>(fadeOut->instance());
		add_child(fade);
	}
	//Godot::print("Player count: " + String::num(PlayersContainer::_get_instance()->_players_count()));
}

void godot::CameraController::_open_doors()
{
	//Godot::print("open doors");
	is_open_door = true;
}

void godot::CameraController::_close_doors()
{
	//Godot::print("close doors");
	is_open_door = false;
}

void godot::CameraController::_start_move()
{
	for (int i = 0; i < 4; i++) 
		if ((int)dirs[i] == 2)
			_move(_get_dir_on_index(i));
}

void godot::CameraController::_change_audio_volume()
{
	timer_audio->disconnect("timeout", this, "_change_audio_volume");

	Godot::print(String::num(AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus()))));

	if (AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) >-15)
		return;

	AudioServer::get_singleton()->set_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus()),
		AudioServer::get_singleton()->get_bus_volume_db(AudioServer::get_singleton()->get_bus_index(audio->get_bus())) - delta_step/4);

	timer_audio->connect("timeout", this, "_change_audio_volume");
	timer_audio->start(time_delta);
}

godot::CameraController::CameraController()
{
	player1 = nullptr;
	player2 = nullptr;
}

godot::CameraController::~CameraController()
{
}
