#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

PauseButtons::PauseButtons() {}
PauseButtons::~PauseButtons() {}

void godot::PauseButtons::_init() {}
void godot::PauseButtons::_ready() 
{
	ResourceLoader* rld = ResourceLoader::get_singleton();
	menu_scene = rld->load("res://Assets/Prefabs/Scenes/Menu.tscn");
	set_visible(false);
}

void PauseButtons::_register_methods()
{

	register_method((char*)"_input", &PauseButtons::_input);
	register_method((char*)"_ready", &PauseButtons::_ready);
	register_method((char*)"_on_Quit_pressed", &PauseButtons::_on_Quit_pressed);
	register_method((char*)"_on_Menu_pressed", &PauseButtons::_on_Menu_pressed);
	register_method((char*)"_on_Resume_pressed", &PauseButtons::_on_Resume_pressed);

}

void godot::PauseButtons::_input(Variant event)
{
	InputEvent* _event = event;
	if (_event->is_action_pressed("ui_pause"))
	{
		cast_to<TextureButton>(find_node("Resume"))->grab_focus();
		Godot::print("pause");
		cast_to<Node2D>(get_parent())->set_global_position(cast_to<Node2D>(get_node("/root/Node2D/Node/Camera2D"))->get_global_position());
		
		if (!is_visible()) {
			set_visible(true);
		}
		else {
			set_visible(false);
		}

		//get_tree()->set_pause(true);
	}

}

void godot::PauseButtons::_on_Resume_pressed(Variant)
{
	set_visible(false);
	//get_tree()->set_pause(false);
}


void godot::PauseButtons::_on_Menu_pressed(Variant)
{
	
	auto tree = get_tree();
	tree->change_scene_to(menu_scene);
	//add_child(res->instance());
	//queue_free();
}

void godot::PauseButtons::_on_Quit_pressed(Variant)
{
	_exit_tree();
}
