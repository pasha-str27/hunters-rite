#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Key::_register_methods()
{
	register_method("_init", &Key::_init);
	register_method("_get_type", &Key::_get_type);
	register_method("_on_Area2D_body_entered", &Key::_on_Area2D_body_entered);
	
	register_property<Key, String>("key_type", &Key::key_type, "");
	register_property<Key, Color>("key_color", &Key::key_color, Color(0,0,0));
}

void godot::Key::_init()
{
}

void godot::Key::_ready()
{
}

String godot::Key::_get_type()
{
	return key_type;
}

void godot::Key::_on_Area2D_body_entered(Node* node)
{
	if (node->is_in_group("player"))
	{
		//key holder
		HBoxContainer* key_box = nullptr;
		key_box = cast_to<HBoxContainer>(get_node("/root/Node2D/Node/Camera2D/KeyHolder/Keyses/Keys"));

		//open next key/boss room
		PlayersContainer::_get_instance()->_add_key(_get_type());

		//key types and key color
		std::vector<String> name_keys{ "key_A", "key_B","key_C", "key_D", "key_E", "key_F" };
		std::vector<Color> keys_color{ Color(1, 1, 0),Color(1, 0, 0), Color(0, 1, 0) };

		Godot::print("-----------Key_type-----------");
		Godot::print(_get_type());
		Godot::print("-----------Key_type-----------");
		
		//find key and set key color/visible
		for (int i = 0; i < 5; i++) {
			if (_get_type() == name_keys[i]) {

				auto key_container = CustomExtensions::IsIncludedInChildrenWithName(key_box, _get_type());

				if (key_container != nullptr) {
					Control* key = cast_to<Control>(key_container->get_child(1));
					key->set_visible(true);
					key->set_modulate(keys_color[i]);
				}

				queue_free();
				return;
			}
		}
	}
}


godot::Key::Key()
{
	key_type = "";
}

godot::Key::~Key()
{
}
