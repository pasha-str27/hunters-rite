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
	ResourceLoader* resource_loader = ResourceLoader::get_singleton();
	menu_scene = resource_loader->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	timer_music_out = Timer::_new();
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
		if (PlayersContainer::_get_instance()->_get_player1_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player1_regular()->get_child(1)->call("_change_moving", false);

		if (PlayersContainer::_get_instance()->_get_player2_regular() != nullptr)
			PlayersContainer::_get_instance()->_get_player2_regular()->call("_change_moving", false);

		if (GameManager::current_level == 10 || MenuButtons::game_type==TUTORIAL)
		{
			MenuButtons::was_loaded = false;
			add_child(fade_out->instance());

			if (timer_music_out == nullptr)
			{
				timer_music_out = Timer::_new();
				add_child(timer_music_out);
			}

			timer_music_out->connect("timeout", this, "_audio_fade_to_main_menu");
			timer_music_out->start(0.01);


			if (timer == nullptr)
			{
				timer = Timer::_new();
				add_child(timer);
			}
			timer->connect("timeout", this, "_move_to_main_menu");
			timer->start(1);
			Enemies::get_singleton()->_clear();
			return;
		}

			timer_music_out->connect("timeout", this, "_audio_fade_to_main_menu");
			timer_music_out->start(0.01);

			timer->connect("timeout", this, "_move_to_main_menu");
			timer->start(1);
			Enemies::get_singleton()->_clear();
			return;
		}

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
	Enemies::get_singleton()->_clear();
	PlayersContainer::_get_instance()->_clear_keys();
	camera->call("_go_to_start");

	if (PlayersContainer::_get_instance()->_get_player1() != nullptr)
		PlayersContainer::_get_instance()->_get_player1()->call("_change_moving", true);

	_try_to_change_player_moving(PlayersContainer::_get_instance()->_get_player1(), true);
	_try_to_change_player_moving(PlayersContainer::_get_instance()->_get_player2(), true);

	// clearing items on level
	auto children_item = get_node("/root/Node2D/Items")->get_children();
	for (int i = 0; i < children_item.size(); i++)
		cast_to<Node2D>(children_item[i])->queue_free();

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
	if (AudioController::get_singleton()->_mute_audio(timer_audio, this))
		return;
}

void godot::ExitHandler::_audio_fade_to_main_menu()
{
	if (AudioController::get_singleton()->_audio_fade_to_main_menu(timer_music_out, this))
		return;
}

void godot::ExitHandler::_move_to_main_menu()
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	menu_scene = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	get_node("/root")->add_child(menu_scene->instance());
	get_node("/root/Node2D")->queue_free();
	get_parent()->queue_free();
	PlayersContainer::_get_instance()->_clear();
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
