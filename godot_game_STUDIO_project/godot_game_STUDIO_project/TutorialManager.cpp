#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::TutorialManager::_register_methods()
{
	register_method("_init", &TutorialManager::_init);
	register_method("_ready", &TutorialManager::_ready);
	register_method("_door_collision", &TutorialManager::_door_collision);
	register_method("_close_doors", &TutorialManager::_close_doors);
	register_method("_open_doors", &TutorialManager::_open_doors);
	register_method("_start_move", &TutorialManager::_start_move);
	register_method("_change_audio_volume", &TutorialManager::_change_audio_volume);
	register_method("_mute_audio_volume", &TutorialManager::_mute_audio_volume);
	register_method("_start_mute_volume", &TutorialManager::_start_mute_volume);
	register_method("_input", &TutorialManager::_input);
	register_method("_audio_fade_to_main_menu", &TutorialManager::_audio_fade_to_main_menu);
	register_method("_spawn_exit", &TutorialManager::_spawn_exit);
	register_method("_set_current_room_type", &TutorialManager::_set_current_room_type);
	register_method("_go_to_start", &TutorialManager::_go_to_start);
	register_method("_get_type_keys", &TutorialManager::_get_type_keys);
	register_method("_show_game_over_screen", &TutorialManager::_show_game_over_screen);

	register_property<TutorialManager, Ref<PackedScene>>("Fade In Animation", &TutorialManager::fadeIn, nullptr);
	register_property<TutorialManager, Ref<PackedScene>>("Fade Out Animation", &TutorialManager::fadeOut, nullptr);
	register_property<TutorialManager, Ref<PackedScene>>("game_back", &TutorialManager::game_back, nullptr);
	register_property<TutorialManager, Ref<PackedScene>>("boss_back", &TutorialManager::boss_back, nullptr);
	register_property<TutorialManager, Ref<PackedScene>>("pause_menu", &TutorialManager::pause_menu, nullptr);
	register_property<TutorialManager, Ref<PackedScene>>("Exit", &TutorialManager::exit, nullptr);
}

void godot::TutorialManager::_move(String dir)
{
	_close_doors();

	auto fade = cast_to<Node2D>(fadeIn->instance());
	add_child(fade);

	auto generation_node = get_parent()->get_node("Generation");

	auto prev_room = CurrentRoom::get_singleton()->_get_current_room();

	if (dir == "top")
	{
		float delta = 720;

		set_global_position(get_global_position() - Vector2(0, delta));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "DownDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		CurrentRoom::get_singleton()->_set_current_room(next_room);

		if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
			cast_to<Node2D>(PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1))->set_global_position(move_point->get_global_position());

		if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player2_regular()->set_global_position(move_point->get_global_position());
	}

	if (dir == "bottom")
	{
		float delta = 720;

		set_global_position(get_global_position() + Vector2(0, delta));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "UpDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		CurrentRoom::get_singleton()->_set_current_room(next_room);

		if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
			cast_to<Node2D>(PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1))->set_global_position(move_point->get_global_position());

		if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player2_regular()->set_global_position(move_point->get_global_position());
	}

	if (dir == "left")
	{
		float delta = 1024;

		set_global_position(get_global_position() - Vector2(delta, 0));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "RightDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		CurrentRoom::get_singleton()->_set_current_room(next_room);

		if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
			cast_to<Node2D>(PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1))->set_global_position(move_point->get_global_position());

		if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player2_regular()->set_global_position(move_point->get_global_position());
	}

	if (dir == "right")
	{
		float delta = 1024;

		set_global_position(get_global_position() + Vector2(delta, 0));

		Node2D* next_room = generation_node->call("_get_next_room", get_global_position());
		Node2D* door = CustomExtensions::GetChildByWordInName(next_room, "LeftDoor");
		Node2D* move_point = cast_to<Node2D>(door->get_node("SpawnPoint"));

		CurrentRoom::get_singleton()->_set_current_room(next_room);

		if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
			cast_to<Node2D>(PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1))->set_global_position(move_point->get_global_position());

		if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player2_regular()->set_global_position(move_point->get_global_position());
	}

	auto cur_room = CurrentRoom::get_singleton()->_get_current_room();

	if ((String)prev_room->call("_get_room_type") == "tut_room" && (String)cur_room->call("_get_room_type") == "heal_room")
	{
		auto player = PlayersContainer::_get_instance()->_get_player1_regular();
		if (player != nullptr)
			player->get_child(1)->call("_set_HP", (float)player->get_child(1)->call("_get_HP") / 2);

		player = PlayersContainer::_get_instance()->_get_player2_regular();
		if (player != nullptr)
			player->call("_set_HP", (float)player->call("_get_HP") / 2);
	}

	if ((String)prev_room->call("_get_room_type") == "heal_room" && (String)cur_room->call("_get_room_type") == "tut_room")
	{
		auto player = PlayersContainer::_get_instance()->_get_player1_regular();
		if (player != nullptr)
			player->get_child(1)->call("_set_HP", (float)player->get_child(1)->call("_get_max_HP"));

		player = PlayersContainer::_get_instance()->_get_player2_regular();
		if (player != nullptr)
			player->call("_set_HP", (float)player->call("_get_max_HP"));
	}

	if ((String)prev_room->call("_get_room_type") == "heal_room" && (String)cur_room->call("_get_room_type") == "revive_room")
	{
		auto player = PlayersContainer::_get_instance()->_get_player1_regular();
		if (player != nullptr)
			player->get_child(1)->call("_die");
		cast_to<Node2D>(player->get_child(1))->set_global_position(prev_room->get_global_position()+Vector2(0,720));
	}

	if ((String)prev_room->call("_get_room_type") == "revive_room" && (String)cur_room->call("_get_room_type") == "heal_room")
	{
		auto player = PlayersContainer::_get_instance()->_get_player2_regular();
		if (player != nullptr)
			player->call_deferred("_player_to_ghost");
	}

	if ((String)cur_room->call("_get_room_type") == "heal_room")
		cur_room->get_node("Stone")->call("_can_heal_true");

	if (minimap != nullptr)
		minimap->call("_update_minimap");
}

String godot::TutorialManager::_get_dir_on_index(int i)
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

bool godot::TutorialManager::_is_one_player_alive()
{
	return !PlayersContainer::_get_instance()->_get_player1() || !PlayersContainer::_get_instance()->_get_player2();
}

void godot::TutorialManager::_init()
{
	for (int i = 0; i < 4; i++)
		dirs.push_back(0);
}

void  godot::TutorialManager::_hide_tutorial_sprites(String t_player_name) {

	// clear coop tutorial 
	cast_to<Node2D>(get_node("/root/Node2D/Node/TutorialSprites"))->hide();

	Control* tutorial_control = nullptr;
	tutorial_control = cast_to<Control>(get_node("/root/Node2D/Node/TutorialSpritesSingle/TutorialControl"));

	// attack move special
	Array tutorial_sprites = tutorial_control->get_children();

	for (int child_index = 0; child_index < tutorial_sprites.size(); child_index++) {

		//hide tutorial for other player
		auto sprite_box = cast_to<Node2D>(tutorial_sprites[child_index])->get_child(2);
		cast_to<TextureRect>(sprite_box->find_node(cast_to<Area2D>(tutorial_sprites[child_index])->get_name() + t_player_name))->set_visible(false);
		cast_to<HBoxContainer>(get_node("/root/Node2D/Node/TutorialSpritesSingle/TutorialNextRoom"))->set_visible(false);
		cast_to<CenterContainer>(sprite_box->find_node(t_player_name))->set_visible(false);
	}
}

void godot::TutorialManager::_spawn_players()
{
	ResourceLoader* loader = ResourceLoader::get_singleton();
	if (MenuButtons::game_mode == SHOOTER)
	{
		Ref<PackedScene> pl1 = loader->load("res://Assets/Prefabs/Players/Player1.tscn");
		Node2D* player = cast_to<Node2D>(pl1->instance());
		get_parent()->call_deferred("add_child", player);
		player1 = player;
		player2 = nullptr;
		PlayersContainer::_get_instance()->_set_player1_regular(player1);
		PlayersContainer::_get_instance()->_set_player2_regular(player2);
		get_node("P2HealthBarWrapper")->queue_free();
		_hide_tutorial_sprites("P2");
		//	hiding label
		//get_node("P1HealthBarWrapper/Label")->queue_free();
	}
	else
	{
		if (MenuButtons::game_mode == MELEE)
		{
			Ref<PackedScene> pl2 = loader->load("res://Assets/Prefabs/Players/Player2.tscn");
			Node2D* player = cast_to<Node2D>(pl2->instance());
			get_parent()->call_deferred("add_child", player);
			player2 = player;
			player1 = nullptr;
			PlayersContainer::_get_instance()->_set_player1_regular(player1);
			PlayersContainer::_get_instance()->_set_player2_regular(player2);
			get_node("P1HealthBarWrapper")->queue_free();
			_hide_tutorial_sprites("P1");
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

			PlayersContainer::_get_instance()->_set_player1_regular(player1);
			PlayersContainer::_get_instance()->_set_player2_regular(player2);

			cast_to<Node2D>(get_node("/root/Node2D/Node/TutorialSpritesSingle"))->hide();

			if (player2->has_method("_set_controll_buttons"))
				player2->call_deferred("_set_controll_buttons", "Player2_up", "Player2_down", "Player2_left", "Player2_right", "Player2_fight_up", "Player2_fight_down", "Player2_fight_left", "Player2_fight_right", "Player2_special");
			else
			{
				for (int i = 0; i < player2->get_child_count(); ++i)
					if (player2->get_child(i)->has_method("_set_controll_buttons"))
					{
						player2->get_child(i)->call_deferred("_set_controll_buttons", "Player2_up", "Player2_down", "Player2_left", "Player2_right", "Player2_fight_up", "Player2_fight_down", "Player2_fight_left", "Player2_fight_right", "Player2_special");
						break;
					}
			}

			if (player1->has_method("_set_controll_buttons"))
				player1->call_deferred("_set_controll_buttons", "Player1_up", "Player1_down", "Player1_left", "Player1_right", "Player1_fight_up", "Player1_fight_down", "Player1_fight_left", "Player1_fight_right", "Player1_special");
			else
			{
				for (int i = 0; i < player1->get_child_count(); ++i)
					if (player1->get_child(i)->has_method("_set_controll_buttons"))
					{
						player1->get_child(i)->call_deferred("_set_controll_buttons", "Player1_up", "Player1_down", "Player1_left", "Player1_right", "Player1_fight_up", "Player1_fight_down", "Player1_fight_left", "Player1_fight_right", "Player1_special");
						break;
					}
			}

			//PlayersContainer::_get_instance()->_set_player1(player1);
			//PlayersContainer::_get_instance()->_set_player2(player2);
		}
	}
}

bool godot::TutorialManager::_is_player_have_need_keys(Color rooms_key)
{
	if (rooms_key==Color())
		return true;

	Array players_keys = PlayersContainer::_get_instance()->_get_key_list();

	for (int i = 0; i < players_keys.size(); ++i)
		if (players_keys[i] == rooms_key)
			return true;

	return false;
}

void godot::TutorialManager::_ready()
{
	minimap = cast_to<CanvasItem>(get_node("MiniMap"));

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
}

void godot::TutorialManager::_door_collision(String door_dir)
{
	if (Enemies::get_singleton()->_get_enemies_count() != 0 || Enemies::get_singleton()->spawning())
		return;

	if (MenuButtons::game_mode == COOP && (PlayersContainer::_get_instance()->_get_player1() == nullptr
		|| PlayersContainer::_get_instance()->_get_player2() == nullptr))
		return;

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
		if ((int)dirs[index] > 0)
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

	if (!_is_player_have_need_keys((Color)next_room->call("_get_last_key_color")))
		return;

	if (((int)dirs[index] == 2 && MenuButtons::game_mode == COOP) || ((MenuButtons::game_mode == SHOOTER || MenuButtons::game_mode == MELEE) && (int)dirs[index] == 1))
	{
		Enemies::get_singleton()->set_spawning(true);

		if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1)->call("_change_moving", false);

		if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player2_regular()->call("_change_moving", false);

		auto fade = cast_to<Node2D>(fadeOut->instance());
		add_child(fade);
	}
}

void godot::TutorialManager::_open_doors()
{
	if (current_room_type == "boss")
	{
		_spawn_exit();
		current_room_type = "";
	}

	is_open_door = true;
}

void godot::TutorialManager::_close_doors()
{
	//current_room->call("_spawn_enemies");
	is_open_door = false;
}

void godot::TutorialManager::_start_move()
{
	for (int i = 0; i < 4; i++)
		if ((int)dirs[i] == 2 || (_is_one_player_alive() && (int)dirs[i] == 1))
		{
			_move(_get_dir_on_index(i));
			for (int i = 0; i < 4; i++)
				dirs[i] = 0;
		}
}

void godot::TutorialManager::_change_audio_volume()
{
	if (AudioController::get_singleton()->_change_audio_volume_camera_controller(timer_audio, this, audio, time_delta))
		return;
}

void godot::TutorialManager::_mute_audio_volume()
{
	if (AudioController::get_singleton()->_mute_audio_volume(timer_audio, this, audio, time_delta))
		return;
}

void godot::TutorialManager::_start_mute_volume()
{
	timer_audio->connect("timeout", this, "_mute_audio_volume");
	timer_audio->start(time_delta);
}

void godot::TutorialManager::_input(Variant event)
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

	if (Input::get_singleton()->is_action_just_pressed("ui_show_minimap"))
		if (minimap != nullptr)
		{
			if (!is_showing_minimap)
				minimap->show();
			else
				minimap->hide();

			is_showing_minimap = !is_showing_minimap;
		}
}

void godot::TutorialManager::_audio_fade_to_main_menu()
{
	if (AudioController::get_singleton()->_audio_fade_to_main_menu(timer_audio, this, audio, time_delta))
		return;
}

void godot::TutorialManager::_spawn_exit()
{
	auto exit_node = cast_to<Node2D>(exit->instance());
	exit_node->set_global_position(this->get_global_position());
	get_node("/root/Node2D/Node/")->add_child(exit_node);
}

void godot::TutorialManager::_set_current_room_type(String type)
{
	current_room_type = type;
}

void godot::TutorialManager::_get_type_keys()
{

	generated_keys.clear();

	HBoxContainer* key_box = nullptr;
	key_box = cast_to<HBoxContainer>(get_node("/root/Node2D/Node/Camera2D/KeyHolder/Keyses/Keys"));

	//key and key_holder texture
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<Texture> res = rld->load("res://Assets/Sprites/UI/BacksButtonsAndOther/backround_key.png");
	Ref<Texture> key_texture = rld->load("res://Assets/Sprites/Items/key.png");

	//get new generated keys
	std::vector<Node2D*> key_types = CustomExtensions::GetChildrenByWordInName(cast_to<Node2D>(get_node("/root/Node2D/Node/Generation")), "Key");
	Godot::print("------gen_key_v2------");
	for (auto i : key_types) {
		generated_keys.push_back(String(i->call("_get_type")));
		Godot::print(String(i->call("_get_type")));
	}
	Godot::print("------gen_key_v2------");


	//clear key holders
	for (int i = 0; i < key_box->get_children().size(); i++) {
		cast_to<CenterContainer>(key_box->get_children()[i])->queue_free();
	}

	//add key sprites in key holder
	for (int i = 0; i < generated_keys.size(); i++) {

		auto key_sprite = TextureRect::_new();
		key_sprite->set_texture(key_texture);

		auto item_bacground = TextureRect::_new();
		item_bacground->set_texture(res);

		auto control = Control::_new();
		control->set_name("key_sprite");
		control->add_child(key_sprite);
		control->set_custom_minimum_size(Vector2(64, 64));
		control->set_visible(false);

		auto container = CenterContainer::_new();
		container->add_child(item_bacground);
		container->add_child(control);
		container->set_name(generated_keys[i]);

		key_box->add_child(container);
	}
}

void godot::TutorialManager::_go_to_start()
{
	auto fade = cast_to<Node2D>(fadeIn->instance());
	add_child(fade);

	timer_audio->connect("timeout", this, "_change_audio_volume");
	timer_audio->start(time_delta);

	set_global_position(Vector2(0, 0));

	player1 = PlayersContainer::_get_instance()->_get_player1_regular();
	player2 = PlayersContainer::_get_instance()->_get_player2_regular();

	if (player1 != nullptr)
	{
		player1->get_child(1)->call("_ghost_to_player");
		cast_to<Node2D>(player1->get_child(1))->set_global_position(Vector2(0, -50));
	}

	if (player2 != nullptr)
	{
		player2->call("_ghost_to_player");
		player2->set_global_position(Vector2(0, 50));
	}
}

godot::TutorialManager::TutorialManager()
{
	player1 = nullptr;
	player2 = nullptr;
}

godot::TutorialManager::~TutorialManager()
{
	audio = nullptr;
	audio_boss = nullptr;
	timer_audio = nullptr;
	audio_server = nullptr;
	player1 = nullptr;
	player2 = nullptr;
}

void godot::TutorialManager::_show_game_over_screen()
{
	cast_to<Timer>(get_node("game_over"))->disconnect("timeout", this, "_show_game_over_screen");
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<PackedScene> game_over_screen = rld->load("res://Assets/Prefabs/Scenes/GameOver.tscn");
	add_child(game_over_screen->instance());
	get_tree()->set_pause(true);
}