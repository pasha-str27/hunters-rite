#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Item::_register_methods()
{
	register_method("_ready", &Item::_ready);
	register_method("_init", &Item::_init);
	register_method("_on_Area2D_body_entered", &Item::_on_Area2D_body_entered);

	register_property<Item, String>("Name", &Item::name, "");
	register_property<Item, float>("speed", &Item::speed, 1000);
	register_property<Item, float>("HP", &Item::HP, 1000);
	register_property<Item, float>("damage", &Item::damage, 1000);
	register_property<Item, float>("attack_speed_delta", &Item::attack_speed_delta, 1000);
	register_property<Item, int>("number_to_next_item", &Item::number_to_next_item, 1000);
	register_property<Item, bool>("decrease_attack_radius", &Item::decrease_attack_radius, false);
	register_property<Item, bool>("encrease_attack_radius", &Item::encrease_attack_radius, false);
	register_property<Item, bool>("Is Buff", &Item::is_buff, true);
}

godot::Item::Item()
{
	items_counter = 1;
	HP = 0;
	attack_speed_delta = 1;
	damage = 0;
	decrease_attack_radius = false;
	encrease_attack_radius = false;
	number_to_next_item = 0;
	speed = 0;
}

godot::Item::~Item()
{
	animator = nullptr;
}

void godot::Item::_ready()
{
	animator = cast_to<AnimationPlayer>(get_child(0)->get_child(0));
	animator->play("idle");
}

void godot::Item::_on_Area2D_body_entered(Node* node)
{
	VBoxContainer* item_box = nullptr;

	if (!node->is_in_group("player"))
		return;

	if (!(bool)node->call("_is_alive"))
		return;

	_apply_item(node);
	
	if (node->is_in_group("player2"))
		//getting item box for player 2
		item_box = cast_to<VBoxContainer>(get_node("/root/Node2D/Node/Camera2D/ItemHolder/P2Items"));
	else
		//getting item box for player 1
		item_box = cast_to<VBoxContainer>(get_node("/root/Node2D/Node/Camera2D/ItemHolder/P1Items"));

	//creating container for item
	auto control = _create_control();

	//adding item to item box
	auto item_in_box = CustomExtensions::IsIncludedInChildrenWithName(item_box, name);
	if (item_in_box != nullptr)
	{
		//get label and set counter +1
		auto label_in_item = cast_to<Label>(item_in_box->get_child(2));
		label_in_item->set_visible(true);
		String items_amount = label_in_item->get_text();
		items_amount.erase(0, 1); //erase symbol "x"
		items_counter = items_amount.to_int();
		items_counter++;
		label_in_item->set_text("x" + String::num(items_counter));
	}
	else 
		item_box->add_child(control);

	node->call("_start_item_particles", is_buff);
	queue_free();	
}

Control* godot::Item::_create_control()
{
	//creating new sprite for item in item box
	auto item_sprite = _create_item_sprite();

	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<Texture> res = rld->load("res://Assets/Sprites/UI/BacksButtonsAndOther/bg_Item.png");
	//creating backdound for item in item box
	auto item_background = _create_item_background(res);

	Ref<Theme> theme = rld->load("res://Assets/Font/font_theme.tres");
	rld = nullptr;

	auto text = _create_text(theme);

	auto control = Control::_new();
	control->set_name(name);
	control->set_custom_minimum_size(Vector2(28, 28));
	control->set_scale(Vector2(0.7, 0.7));
	control->add_child(item_background);
	control->add_child(item_sprite);
	control->add_child(text);
	return control;
}

TextureRect* godot::Item::_create_item_sprite()
{
	auto item_sprite = TextureRect::_new();
	item_sprite->set_texture(cast_to<Sprite>(get_child(0))->get_texture());
	item_sprite->set_position(Vector2(-15, -15));
	return item_sprite;
}

TextureRect* godot::Item::_create_item_background(Ref<Texture> res)
{
	auto item_background = TextureRect::_new();
	item_background->set_texture(res);
	item_background->set_position(Vector2(-15, -15));
	item_background->set_modulate(Color(1, 1, 1, 0.6f));
	item_background->set_scale(Vector2(0.7, 0.7));
	return item_background;
}

Label* godot::Item::_create_text(Ref<Theme> theme)
{
	//create label and set parameters for him
	auto text = Label::_new();
	text->set_name("counter");
	text->set_visible(false);
	text->set_theme(theme);
	text->set_position(Vector2(5, 6));
	text->set_text("x" + String::num(items_counter));
	return text;
}

void godot::Item::_apply_item(Node* player)
{
	// speed max 350 / min 100
	// damage max 150 /  min 10
	// max Hp 1000 / min 50

	float player_speed = player->call("_get_speed");
	float player_damage = player->call("_get_damage");
	float player_max_hp = player->call("_get_max_HP");
	int player_number_to_item = player->call("_get_number_to_next_item");
	float player_attack_speed_delta = player->call("_get_attack_speed_delta");

	if ((player_speed + speed <= 100) || (player_speed + speed >= 350))
		speed = 0;

	player->call("_set_speed", player_speed + speed);

	if ((player_damage + damage <= 10) || (player_damage + damage >= 150))
		damage = 0;

	player->call("_set_damage", player_damage + damage);

	if ((player_max_hp + HP >= 1000) || (player_max_hp + HP <= 50))
		HP = 0;

	player->call("_set_max_HP", player_max_hp + HP);

	player->call("_set_number_to_next_item", player_number_to_item + number_to_next_item);
	player->call("_set_attack_speed_delta", player_attack_speed_delta * attack_speed_delta);

	if (player->is_in_group("player2"))
	{
		if (decrease_attack_radius)
			player->call("_decrease_attack_radius");

		if (encrease_attack_radius)
			player->call("_encrease_attack_radius");
	}
}

void godot::Item::_init()
{
}