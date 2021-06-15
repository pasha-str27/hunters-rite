#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

Node2D* CameraController::current_room = nullptr;
bool CameraController::show_tutorial = true;

void godot::CameraController::_register_methods()
{
	register_method("_init", &CameraController::_init);
	register_method("_ready", &CameraController::_ready);
	register_method("_door_collision", &CameraController::_door_collision);
	register_method("_close_doors", &CameraController::_close_doors);
	register_method("_open_doors", &CameraController::_open_doors);
	register_method("_start_move", &CameraController::_start_move);
	register_method("_change_audio_volume", &CameraController::_change_audio_volume);
	register_method("_mute_audio_volume", &CameraController::_mute_audio_volume);
	register_method("_start_mute_volume", &CameraController::_start_mute_volume);
	register_method("_input", &CameraController::_input);
	register_method("_audio_fade_to_main_menu", &CameraController::_audio_fade_to_main_menu);
	register_method("_spawn_exit", &CameraController::_spawn_exit);
	register_method("_set_current_room_type", &CameraController::_set_current_room_type);
	register_method("_go_to_start", &CameraController::_go_to_start);

	register_property<CameraController, Ref<PackedScene>>("Fade In Animation", &CameraController::fadeIn, nullptr);
	register_property<CameraController, Ref<PackedScene>>("Fade Out Animation", &CameraController::fadeOut, nullptr);
	register_property<CameraController, Ref<PackedScene>>("game_back", &CameraController::game_back, nullptr);
	register_property<CameraController, Ref<PackedScene>>("boss_back", &CameraController::boss_back, nullptr);
	register_property<CameraController, Ref<PackedScene>>("pause_menu", &CameraController::pause_menu, nullptr);
	register_property<CameraController, Ref<PackedScene>>("Exit", &CameraController::exit, nullptr);
}

void godot::CameraController::_move(String dir)
{
	_close_doors();

	auto fade = cast_to<Node2D>(fadeIn->instance());
	add_child(fade);

	float vertical_offset = 390;
	float horizontal_offset = 250;

	auto generation_node = get_parent()->get_node("Generation");

	if (dir == "top")
	{
		float delta = 720;

		set_global_position(get_global_position() - Vector2(0, delta));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "DownDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		current_room = next_room;

		if (has_node("/root/Node2D/Node/Player1"))
			cast_to<Node2D>(player1->get_node("Player1"))->set_global_position(move_point->get_global_position());

		if (has_node("/root/Node2D/Node/Player2"))
			player2->set_global_position(move_point->get_global_position());
	}

	if (dir == "bottom")
	{
		float delta = 720;

		set_global_position(get_global_position() + Vector2(0, delta));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "UpDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		current_room = next_room;

		if (has_node("/root/Node2D/Node/Player1"))
			cast_to<Node2D>(player1->get_node("Player1"))->set_global_position(move_point->get_global_position());

		if (has_node("/root/Node2D/Node/Player2"))
			player2->set_global_position(move_point->get_global_position());
	}

	if (dir == "left")
	{
		float delta = 1024;

		set_global_position(get_global_position() - Vector2(delta, 0));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "RightDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		current_room = next_room;

		if (has_node("/root/Node2D/Node/Player1"))
			cast_to<Node2D>(player1->get_node("Player1"))->set_global_position(move_point->get_global_position());

		if (has_node("/root/Node2D/Node/Player2"))
			player2->set_global_position(move_point->get_global_position());
	}

	if (dir == "right")
	{
		float delta = 1024;

		set_global_position(get_global_position() + Vector2(delta, 0));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "LeftDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		current_room = next_room;

		if (has_node("/root/Node2D/Node/Player1"))
			cast_to<Node2D>(player1->get_node("Player1"))->set_global_position(move_point->get_global_position());

		if (has_node("/root/Node2D/Node/Player2"))
			player2->set_global_position(move_point->get_global_position());
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

bool godot::CameraController::_is_one_player_alive()
{
	return !has_node("/root/Node2D/Node/Player1") || !has_node("/root/Node2D/Node/Player2");
}

void godot::CameraController::hide_tutorial()
{
	get_parent()->get_node("TutorialSprites")->queue_free();
}

void godot::CameraController::_init()
{
	for (int i = 0; i < 4; i++)
		dirs.push_back(0);
}

void godot::CameraController::_spawn_players()
{
	ResourceLoader* loader = ResourceLoader::get_singleton();
	if (MenuButtons::player_name == 2)
	{
		Ref<PackedScene> pl1 = loader->load("res://Assets/Prefabs/Players/Player1.tscn");
		Node2D* player = cast_to<Node2D>(pl1->instance());
		get_parent()->call_deferred("add_child", player);
		player1 = player;
		player2 = nullptr;
		//PlayersContainer::_get_instance()->_set_player1(player1);
		//PlayersContainer::_get_instance()->_set_player2(player2);
		get_node("P2HealthBarWrapper")->queue_free();
		//	hiding label
		//get_node("P1HealthBarWrapper/Label")->queue_free();
	}
	else
	{
		if (MenuButtons::player_name == 1)
		{
			Ref<PackedScene> pl2 = loader->load("res://Assets/Prefabs/Players/Player2.tscn");
			Node2D* player = cast_to<Node2D>(pl2->instance());
			get_parent()->call_deferred("add_child", player);
			player2 = player;
			player1 = nullptr;
			//PlayersContainer::_get_instance()->_set_player1(player1);
			//PlayersContainer::_get_instance()->_set_player2(player2);
			get_node("P1HealthBarWrapper")->queue_free();
			//	hiding label
			//get_node("P2HealthBarWrapper/Label")->queue_free();
		}
		else
		{
			Ref<PackedScene> pl1 = loader->load("res://Assets/Prefabs/Players/Player1.tscn");
			Node2D* player_1 = cast_to<Node2D>(pl1->instance());
			get_parent()->call_deferred("add_child", player_1);
			player1 = player_1;

			Ref<PackedScene> pl2 = loader->load("res://Assets/Prefabs/Players/Player2.tscn");
			Node2D* player_2 = cast_to<Node2D>(pl2->instance());
			get_parent()->call_deferred("add_child", player_2);
			player2 = player_2;

			//PlayersContainer::_get_instance()->_set_player1(player1);
			//PlayersContainer::_get_instance()->_set_player2(player2);
		}
	}
}

bool godot::CameraController::_is_player_have_need_keys(Array rooms_keys)
{
	if (rooms_keys.size() == 0)
		return true;

	Array players_keys = PlayersContainer::_get_instance()->_get_key_list();

	if (players_keys.size() == 0)
		return false;

	bool check_result = true;
	for (int i = 0; i < rooms_keys.size(); ++i)
	{
		String row = rooms_keys[i];
		for (int k = 0; k < players_keys.size(); ++k)
			check_result = row.find(players_keys[k])!=-1 ? true : false;
	}

	return check_result;
}

void godot::CameraController::_ready()
{
	audio_server = AudioServer::get_singleton();
	_set_current(true);

	_spawn_players();

	if (find_parent("root") != nullptr && !find_parent("root")->has_node("MenuGameMusic"))
	{
		audio = cast_to<AudioStreamPlayer2D>(game_back->instance());
		audio_boss = cast_to<AudioStreamPlayer2D>(boss_back->instance());
		add_child(audio);
		add_child(audio_boss);
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()), -80);
		audio_server->set_bus_volume_db(audio_server->get_bus_index(audio->get_bus()) + 1, -80);
	}

	timer_audio = Timer::_new();
	add_child(timer_audio);
	timer_audio->connect("timeout", this, "_change_audio_volume");
	timer_audio->start(time_delta);

	if (!show_tutorial)
		hide_tutorial();
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
		if((int)dirs[index] > 0)
			dirs[index] = (int)dirs[index] - 1;
		return;
	}

	dirs[index] = (int)dirs[index] + 1;

	Vector2 new_pos;

	switch (index)
	{
	case 0:
	{
		float delta = 1024;
		new_pos = get_global_position() - Vector2(delta, 0);
		break;
	}
	case 1:
	{
		float delta = 1024;
		new_pos = get_global_position() + Vector2(delta, 0);
		break;
	}
	case 2:
	{
		float delta = 720;
		new_pos = get_global_position() - Vector2(0, delta);
		break;
	}
	case 3:
	{
		float delta = 720;
		new_pos = get_global_position() + Vector2(0, delta);
		break;
	}
	default:
		break;
	}

	auto generation_node = get_parent()->get_node("Generation");
	Node2D* next_room = generation_node->call("_get_next_room", new_pos);

	if (!_is_player_have_need_keys((Array)next_room->call("_get_list_of_keys")))
		return;

	if (((int)dirs[index] == 2 && is_open_door && !_is_one_player_alive()) || (_is_one_player_alive() && is_open_door && (int)dirs[index] == 1))
	{
		if(PlayersContainer::_get_instance()->_get_player1() != nullptr)
			PlayersContainer::_get_instance()->_get_player1()->call("_change_moving", false);

		if (PlayersContainer::_get_instance()->_get_player2() != nullptr)
			PlayersContainer::_get_instance()->_get_player2()->call("_change_moving", false);

		auto fade = cast_to<Node2D>(fadeOut->instance());
		add_child(fade);
	}
}

void godot::CameraController::_open_doors()
{
	if (current_room_type == "boss")
	{
		_spawn_exit();
		current_room_type = "";
	}

	is_open_door = true;
}

void godot::CameraController::_close_doors()
{
	//current_room->call("_spawn_enemies");
	is_open_door = false;
}

void godot::CameraController::_start_move()
{
	for (int i = 0; i < 4; i++) 
		if ((int)dirs[i] == 2 || (_is_one_player_alive() && (int)dirs[i] == 1))
		{
			_move(_get_dir_on_index(i));
			for (int i = 0; i < 4; i++)
				dirs[i] = 0;
		}
}

void godot::CameraController::_change_audio_volume()
{
	if (AudioController::get_singleton()->_change_audio_volume_camera_controller(timer_audio,this, audio, time_delta))
		return;
}

void godot::CameraController::_mute_audio_volume()
{
	if (AudioController::get_singleton()->_mute_audio_volume(timer_audio, this, audio, time_delta))
		return;
}

void godot::CameraController::_start_mute_volume()
{
	timer_audio->connect("timeout", this, "_mute_audio_volume");
	timer_audio->start(time_delta);
}

void godot::CameraController::_input(Variant event)
{
	if (Input::get_singleton()->is_action_just_pressed("ui_pause"))
	{
		Input::get_singleton()->action_release("ui_pause");
		if (PlayersContainer::_get_instance()->_get_player1() != nullptr)
			PlayersContainer::_get_instance()->_get_player1()->call("_stop_animations");

		if (PlayersContainer::_get_instance()->_get_player2() != nullptr)
			PlayersContainer::_get_instance()->_get_player2()->call("_stop_animations");
		get_tree()->set_pause(true);
		add_child(pause_menu->instance());
	}
}

void godot::CameraController::_audio_fade_to_main_menu()
{
	if (AudioController::get_singleton()->_audio_fade_to_main_menu(timer_audio, this, audio, time_delta))
		return;
}

void godot::CameraController::_spawn_exit()
{
	auto exit_node = cast_to<Node2D>(exit->instance());
	exit_node->set_global_position(this->get_global_position());
	get_node("/root/Node2D/Node/")->add_child(exit_node);
}

void godot::CameraController::_set_current_room_type(String type)
{
	current_room_type = type;
}

void godot::CameraController::_go_to_start()
{
	auto fade = cast_to<Node2D>(fadeIn->instance());
	add_child(fade);

	timer_audio->connect("timeout", this, "_change_audio_volume");
	timer_audio->start(time_delta);

	set_global_position(Vector2(0, 0));

	player1 = PlayersContainer::_get_instance()->_get_player1();
	player2 = PlayersContainer::_get_instance()->_get_player2();

	if (player1 != nullptr)
		player1->set_global_position(Vector2(0, -50));
	else
	{
		if (MenuButtons::player_name == 3)
		{
			ResourceLoader* rld = ResourceLoader::get_singleton();
			Ref<PackedScene> _player1 = rld->load("res://Assets/Prefabs/Players/Player1.tscn");
			Node2D* _player1_node = cast_to<Node2D>(_player1->instance());
			get_parent()->add_child(_player1_node);
			player1 = _player1_node;

			Node* items = get_node("ItemHolder/P1Items");
			for (int i = items->get_child_count() - 1; i >= 0; --i)
				items->get_child(i)->queue_free();
		}
	}

	if (player2 != nullptr)
		player2->set_global_position(Vector2(0, -50));
	else
	{
		if (MenuButtons::player_name == 3)
		{
			ResourceLoader* rld = ResourceLoader::get_singleton();
			Ref<PackedScene> _player2 = rld->load("res://Assets/Prefabs/Players/Player2.tscn");
			Node2D* _player2_node = cast_to<Node2D>(_player2->instance());
			get_parent()->add_child(_player2_node);
			player2 = _player2_node;

			Node* items = get_node("ItemHolder/P2Items");
			for (int i = items->get_child_count() - 1; i >= 0; --i)
				items->get_child(i)->queue_free();
		}
	}
}

godot::CameraController::CameraController()
{
	player1 = nullptr;
	player2 = nullptr;
}

godot::CameraController::~CameraController()
{
	audio = nullptr;
	audio_boss = nullptr;
	timer_audio = nullptr;
	audio_server = nullptr;
	player1 = nullptr;
	player2 = nullptr;
}
