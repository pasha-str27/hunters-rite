#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

void godot::Item::_register_methods()
{
	register_method("_ready", &Item::_ready);
	register_method("_init", &Item::_init);
	register_method("_process", &Item::_process);
	register_method("_on_Area2D_body_entered", &Item::_on_Area2D_body_entered);
	register_method("_get_is_buff", &Item::_get_is_buff);

	register_property<Item, String>("Name", &Item::name, "");
	register_property<Item, float>("speed", &Item::speed, 1000);
	register_property<Item, float>("HP", &Item::HP, 1000);
	register_property<Item, float>("damage", &Item::damage, 1000);
	register_property<Item, float>("attack_speed_delta", &Item::attack_speed_delta, 1000);
	register_property<Item, int>("number_to_next_item", &Item::number_to_next_item, 1000);
	register_property<Item, bool>("decrease_attack_radius", &Item::decrease_attack_radius, false);
	register_property<Item, bool>("encrease_attack_radius", &Item::encrease_attack_radius, false);
	register_property<Item, bool>("Is Buff", &Item::is_buff, true);
	register_property<Item, float>("item_price", &Item::item_price, -1);
}

godot::Item::Item()
{
	items_counter = 1;
	HP = 0;
	attack_speed_delta = 0;
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

	// speed max 350 / min 100
	// damage max 150 /  min 10
	// max Hp 1000 / min 50

	if (((float)node->call("_get_speed") + speed <= 100) || ((float)node->call("_get_speed") + speed >= 380))
		speed = 0;
	if (((float)node->call("_get_damage") + damage <= 10) || ((float)node->call("_get_damage") + damage >= 200))
		damage = 0;
	if (((float)node->call("_get_max_HP") + HP >= 1000) || ((float)node->call("_get_max_HP") + HP <= 50))
		HP = 0;

	node->call("_set_max_HP", (float)node->call("_get_max_HP") + HP);
	node->call("_set_speed", (float)node->call("_get_speed") + speed);
	node->call("_set_damage", (float)node->call("_get_damage") + damage);
	node->call("_set_number_to_next_item", (int)node->call("_get_number_to_next_item") + number_to_next_item);
	node->call("_set_attack_speed_delta", (float)node->call("_get_attack_speed_delta") + attack_speed_delta);

	if (node->is_in_group("player2"))
	{
		if (decrease_attack_radius)
			node->call("_decrease_attack_radius");

		if (encrease_attack_radius)
			node->call("_encrease_attack_radius");

		//getting item box for player 2
		item_box = cast_to<VBoxContainer>(get_node("/root/Node2D/Node/Camera2D/ItemHolder/P2Items"));
	}
	else
		//getting item box for player 1
		item_box = cast_to<VBoxContainer>(get_node("/root/Node2D/Node/Camera2D/ItemHolder/P1Items"));

	//Godot::print(item_box->get_name());
	//creating new sprite for item in item box

	auto item_sprite = TextureRect::_new();
	item_sprite->set_texture(cast_to<Sprite>(get_child(0))->get_texture());
	item_sprite->set_position(Vector2(-15,-15));

	//creating backdound for item in item box
	auto item_bacground = TextureRect::_new();
	ResourceLoader* rld = ResourceLoader::get_singleton();
	Ref<Texture> res = rld->load("res://Assets/Sprites/UI/BacksButtonsAndOther/bg_Item.png");
	item_bacground->set_texture(res);
	item_bacground->set_modulate(Color(1,1,1,0.6f));
	item_bacground->set_scale(Vector2(0.7 , 0.7));
	//res->free();

	//create label and set parameters for him
	auto text = Label::_new();
	Ref<Theme> theme = rld->load("res://Assets/Font/font_theme.tres");
	text->set_name("counter");
	text->set_visible(false);
	text->set_theme(theme);
	text->set_position(Vector2(5,6));
	text->set_text("x" + String::num(items_counter));
	//theme->free();

	//creating container for item
	Ref<PackedScene> background = rld->load("res://Assets/Prefabs/Items/BackgroundItem.tscn");
	
	auto one = (cast_to<Node2D>(background->instance()))->get_child(0);
	auto two = (cast_to<Node2D>(background->instance()))->get_child(1);

	auto control = Control::_new();
	control->set_name(name);
	control->set_custom_minimum_size(Vector2(28, 28));
	control->set_scale(Vector2(0.7, 0.7));
	control->add_child(item_bacground);
	control->add_child(item_sprite);
	control->add_child(text);

	//Node2D* item_in_box = nullptr;
	//item_box->add_child(control);
	////adding item to item box
	auto item_in_box = CustomExtensions::IsIncludedInChildrenWithName(item_box, name);
	////Godot::print(item_in_box->get_name());
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
	{
		item_box->add_child(control);
	}
	//Godot::print("here11");
	////achievement
	//if (item_box->get_children().size() == 12) {
	//	Godot::print("Congratulation you collect all items");
	//}

	node->call("_start_item_particles", is_buff);
	queue_free();	
	//Godot::print("here12");//

}
bool godot::Item::_get_is_buff()
{
	return is_buff;
}

float godot::Item::_get_item_price()
{
	return item_price;
}

void godot::Item::_init()
{
}

void godot::Item::_process()
{
}
