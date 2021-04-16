#include "Generation.h"

void godot::Generation::_register_methods()
{
	register_method((char*)"_ready", &Generation::_ready);
	register_method((char*)"_process", &Generation::_process);
	//	register property
	register_property<Generation, Array>("prefab", &Generation::spritePrefab, {});
}

void godot::Generation::_init() {}

void godot::Generation::_ready()
{
	//	console log
	Godot::print("Generation _ready");

	OS::get_singleton()->set_window_fullscreen(true);

	int min = 32;

	//	instantiating prefabs
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			//	instantiating sprite 
			Sprite* sp = cast_to<Sprite>(cast_to<PackedScene>(spritePrefab[0])->instance());
			//	adding to scene 
			add_child(sp);
			//	transforming created prefab
			sp->set_position(Vector2(min + j * 64, min + i * 64));
		}
	}

}

void godot::Generation::_process(float delta)
{

	if (Input::get_singleton()->is_action_just_pressed("ui_cancel")) {
		Godot::print("exit");
		_exit_tree();
	}
}

godot::Generation::~Generation()
{
}

godot::Generation::Generation()
{
	
}
