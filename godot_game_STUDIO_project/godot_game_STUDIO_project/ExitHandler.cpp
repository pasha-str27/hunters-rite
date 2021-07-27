#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::ExitHandler::_register_methods()
{
	register_method("_ready", &ExitHandler::_ready);
	register_method("_on_Area2D_area_entered", &ExitHandler::_on_Area2D_area_entered);
	register_method("_on_Area2D_area_exited", &ExitHandler::_on_Area2D_area_exited);
	register_method("_load_menu_scene", &ExitHandler::_load_menu_scene);
	register_method("_show_exit", &ExitHandler::_show_exit);
	register_method("_mute_audio", &ExitHandler::_mute_audio);
	register_method("_move_to_main_menu", &ExitHandler::_move_to_main_menu);
	register_method("_audio_fade_to_main_menu", &ExitHandler::_audio_fade_to_main_menu);

	register_property<ExitHandler, Ref<PackedScene>>("Fade Out", &ExitHandler::fade_out, nullptr);
}

void godot::ExitHandler::_init()
{
}

void godot::ExitHandler::_ready()
{
	audio_controller = AudioController::get_singleton();
	add_child(timer_music_out);
	add_child(timer);
	add_child(timer_audio);
	timer->connect("timeout", this, "_show_exit");
	timer->start(.5);
	cast_to<Particles2D>(get_node("SpawnExitParticles"))->set_emitting(true);
	cast_to<AnimationPlayer>(get_node("AnimationPlayer"))->play("show");
	Enemies::get_singleton()->set_spawning(false);
}

void godot::ExitHandler::_on_Area2D_area_entered(Node* other)
{
	if (other->is_in_group("player"))
		players_count++;

	bool is_only_one_alive = CustomExtensions::IsOnlyOnePlayerAlive(other);

	if (((is_only_one_alive && players_count == 1) || players_count == 2) && is_spawned)
	{
		_try_to_change_player_moving(PlayersContainer::_get_instance()->_get_player1(), false);
		_try_to_change_player_moving(PlayersContainer::_get_instance()->_get_player2(), false);

		if (GameManager::current_level == 10 || MenuButtons::game_type == TUTORIAL)
		{
			MenuButtons::was_loaded = false;
			add_child(fade_out->instance());

			timer_music_out->connect("timeout", this, "_audio_fade_to_main_menu");
			timer_music_out->start(0.01);

			timer->connect("timeout", this, "_move_to_main_menu");
			timer->start(1);
			Enemies::get_singleton()->_clear();
			return;
		}

		_spawn_fade_out();

		GameManager::show_tutorial = false;
		GameManager::current_level++;
	}
}

void godot::ExitHandler::_on_Area2D_area_exited(Node* other)
{
	if (other->is_in_group("player"))
		players_count--;
}

void godot::ExitHandler::_load_menu_scene()
{
	timer_audio->connect("timeout", this, "_mute_audio");
	timer_audio->start(0.01);

	auto camera = get_node("/root/Node2D/Node/Camera2D");
	auto generation = get_node("/root/Node2D/Node/Generation");
	//	clear list of enemies
	Enemies::get_singleton()->_clear();
	//	clear picked up keys
	PlayersContainer::_get_instance()->_clear_keys();
	//	moving players to (0,0) of level
	camera->call("_go_to_start");

	_try_to_change_player_moving(PlayersContainer::_get_instance()->_get_player1(), true);
	_try_to_change_player_moving(PlayersContainer::_get_instance()->_get_player2(), true);

	// clearing items on level
	auto children_item = get_node("/root/Node2D/Items")->get_children();
	for (int i = 0; i < children_item.size(); i++)
		cast_to<Node2D>(children_item[i])->queue_free();

	//	rebuild level
	generation->call("_ready");
	queue_free();
}

void godot::ExitHandler::_show_exit()
{
	cast_to<Particles2D>(get_node("SpawnExitParticles"))->set_emitting(false);
	timer->disconnect("timeout", this, "_show_exit");
	is_spawned = true;
}

void godot::ExitHandler::_mute_audio()
{
	if (audio_controller->_mute_audio(timer_audio, this))
		timer_audio->disconnect("timeout", this, "_mute_audio");
}

void godot::ExitHandler::_audio_fade_to_main_menu()
{
	if (audio_controller->_audio_fade_to_main_menu(timer_music_out, this))
		timer_music_out->disconnect("timeout", this, "_audio_fade_to_main_menu");
}

void godot::ExitHandler::_move_to_main_menu()
{
	Ref<PackedScene> menu_scene = ResourceLoader::get_singleton()->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	get_node("/root")->add_child(menu_scene->instance());
	get_node("/root/Node2D")->queue_free();
	get_parent()->queue_free();
	PlayersContainer::_get_instance()->_clear();
}

void godot::ExitHandler::_try_to_change_player_moving(Node2D* player, bool value)
{
	if (player != nullptr)
		player->call("_change_moving", value);
}

void godot::ExitHandler::_spawn_fade_out()
{
	auto fade = cast_to<Node2D>(fade_out->instance());
	CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->add_child(fade);
	//	set anim mode (exit of level)
	fade->get_child(0)->get_child(0)->call("_set_is_exit_anim", true);
}

godot::ExitHandler::ExitHandler()
{
	timer = Timer::_new();
	timer_audio = Timer::_new();
	timer_music_out = Timer::_new();
}

godot::ExitHandler::~ExitHandler()
{
	timer = nullptr;
	timer_audio = nullptr;
	audio_server = nullptr;
	timer_music_out = nullptr;
}
