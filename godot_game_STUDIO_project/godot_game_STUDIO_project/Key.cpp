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
		HBoxContainer* key_box = nullptr;
		PlayersContainer::_get_instance()->_add_key(_get_type());
		
		key_box = cast_to<HBoxContainer>(get_node("/root/Node2D/Node/Camera2D/KeyHolder/Keyses/Keys"));
		ResourceLoader* rld = ResourceLoader::get_singleton();


		//creating new sprite for item in item box
		auto key_sprite = TextureRect::_new();
		Ref<Texture> key_texture = rld->load("res://Assets/Sprites/Items/key.png");
		key_sprite->set_texture(key_texture);
		Godot::print(_get_type());
		key_sprite->set_position(Vector2(-15, -15));
		if (_get_type() == "key_A") {
			key_sprite->set_modulate(Color(1, 1, 0));
		}
		if (_get_type() == "key_B") {
			key_sprite->set_modulate(Color(1, 0, 0));
		}
		if (_get_type() == "key_C") {
			key_sprite->set_modulate(Color(0, 1, 0));
		}

		//res->free();

		//creating backdound for item in item box
		auto item_bacground = TextureRect::_new();
		Ref<Texture> res = rld->load("res://Assets/Sprites/UI/BacksButtonsAndOther/bg_Item.png");
		item_bacground->set_texture(res);
		item_bacground->set_position(Vector2(-15, -15));
		item_bacground->set_modulate(Color(0, 0, 0, 0.6f));
		item_bacground->set_scale(Vector2(0.7, 0.7));

		auto container = CenterContainer::_new();
		container->add_child(item_bacground);
		container->add_child(key_sprite);

		key_box->add_child(container);
		queue_free();
	}
}

godot::Key::Key()
{
	key_type = "";
}

godot::Key::~Key()
{
}
