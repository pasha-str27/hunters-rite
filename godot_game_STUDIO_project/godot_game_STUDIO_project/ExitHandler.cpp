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

	register_property<ExitHandler, Ref<PackedScene>>("Fade Out", &ExitHandler::fade_out, nullptr);
}

void godot::ExitHandler::_init()
{
}

void godot::ExitHandler::_ready()
{
	ResourceLoader* resource_loader = ResourceLoader::get_singleton();
	menu_scene = resource_loader->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	add_child(timer);
	add_child(timer_audio);
	timer->connect("timeout", this, "_show_exit");
	timer->start(.5);
	cast_to<Particles2D>(get_node("SpawnExitParticles"))->set_emitting(true);
	cast_to<AnimationPlayer>(get_node("AnimationPlayer"))->play("show");
}

void godot::ExitHandler::_on_Area2D_area_entered(Node* other)
{
	if (other->is_in_group("player"))
		players_count++;

	bool is_only_one_alive = CustomExtensions::IsOnlyOnePlayerAlive(other);
	if (is_only_one_alive || (players_count == 2))
	{
		if (PlayersContainer::_get_instance()->_get_player1() != nullptr)
			PlayersContainer::_get_instance()->_get_player1()->call("_change_can_moving", false);

		if (PlayersContainer::_get_instance()->_get_player2() != nullptr)
			PlayersContainer::_get_instance()->_get_player2()->call("_change_can_moving", false);

		timer_audio->connect("timeout", this, "_mute_audio");
		timer_audio->start(0.01);

		auto fade = cast_to<Node2D>(fade_out->instance());
		CustomExtensions::GetChildByName(get_node("/root/Node2D/Node"), "Camera2D")->add_child(fade);
		fade->get_child(0)->get_child(0)->call("_set_is_exit_anim", true);
	}
}

void godot::ExitHandler::_on_Area2D_area_exited(Node* other)
{
	if (other->is_in_group("player"))
		players_count--;
}

void godot::ExitHandler::_load_menu_scene()
{
	MenuButtons::was_loaded = false;
	SceneTree* tree = get_tree();
	get_node("/root")->add_child(menu_scene->instance());
	get_parent()->get_parent()->queue_free();
}

void godot::ExitHandler::_show_exit()
{
	cast_to<Particles2D>(get_node("SpawnExitParticles"))->set_emitting(false);
	timer->disconnect("timeout", this, "_show_exit");
}

void godot::ExitHandler::_mute_audio()
{
	timer_audio->disconnect("timeout", this, "_mute_audio");

	if (AudioServer::get_singleton()->get_bus_volume_db(2) <= -75
		&& AudioServer::get_singleton()->get_bus_volume_db(3) <= -75)
		return;

	if (AudioServer::get_singleton()->get_bus_volume_db(2) > -75)
		AudioServer::get_singleton()->set_bus_volume_db(2,
			AudioServer::get_singleton()->get_bus_volume_db(2) - 0.8);

	if (AudioServer::get_singleton()->get_bus_volume_db(3) > -75)
		AudioServer::get_singleton()->set_bus_volume_db(3,
			AudioServer::get_singleton()->get_bus_volume_db(3) - 0.8);

	timer_audio->connect("timeout", this, "_mute_audio");
	timer_audio->start(0.01);
}

godot::ExitHandler::ExitHandler()
{
	timer = Timer::_new();
	timer_audio = Timer::_new();
}

godot::ExitHandler::~ExitHandler()
{
	timer = nullptr;
	timer_audio = nullptr;
}
