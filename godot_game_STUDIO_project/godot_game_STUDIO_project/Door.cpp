//#include "Door.h"
//
//void godot::Door::_register_methods()
//{
//	register_method("_ready", &Door::_ready);
//	register_method("_get_correct_colliding", &Door::_get_correct_colliding);
//	register_method("_check_correct_placing", &Door::_check_correct_placing);
//	register_method("_on_Area2D_area_entered", &Door::_on_Area2D_area_entered);
//	register_method("_on_Area2D_area_exited", &Door::_on_Area2D_area_exited);
//
//	register_property<Door, String>("Direction", &Door::direction, "");
//}
//
//void godot::Door::_init()
//{
//}
//
//void godot::Door::_ready()
//{
//	room_ref = get_parent()->get_parent()->call("_get_instance");
//	timer->connect("timeout", this, "_check_correct_placing");
//	add_child(timer);
//	timer->start(5);
//}
//
//bool godot::Door::_get_correct_colliding()
//{
//	return correct_colliding;
//}
//
//void godot::Door::_check_correct_placing()
//{
//	timer->disconnect("timeout", this, "_check_correct_placing");
//	if (!correct_colliding) {
//		room_ref->PrepareToRespawn(direction);
//	}
//
//		/*Ref<PackedScene> room_to_spawn = nullptr;
//		Vector2 _position = Vector2(0, 0);
//		if (direction == "left") {
//			room_to_spawn = room_ref->generation->right_closed_room;
//			_position = Vector2(room_ref->generation->horizontal_distance_spawn_point, room_ref->get_position().y);
//		}
//		else if (direction == "top") {
//			room_to_spawn = room_ref->generation->bottom_closed_room;
//			_position = Vector2(room_ref->get_position().x, -room_ref->generation->vertical_distance_spawn_point);
//		}
//		else if (direction == "right") {
//			room_to_spawn = room_ref->generation->left_closed_room;
//			_position = Vector2(-room_ref->generation->horizontal_distance_spawn_point, room_ref->get_position().y);
//		}
//		else if (direction == "bottom") {
//			room_to_spawn = room_ref->generation->top_closed_room;
//			_position = Vector2(room_ref->get_position().x, room_ref->generation->vertical_distance_spawn_point);
//		}
//
//		auto n = cast_to<Node2D>(room_to_spawn->instance());
//		n->set_global_position(_position);
//		get_node("/root/Node2D/Rooms")->add_child(n);*/
//}
//
//void godot::Door::_on_Area2D_area_entered(Node* other)
//{
//	if (other->get_name().find("Wall") != -1)
//	{
//		Godot::print("Collision door with wall: " + direction);
//		get_parent()->get_parent()->call_deferred("_add_door_collision", direction);
//	}
//
//	if (other->get_parent()->get_name().find("Door") != -1)
//	{
//		correct_colliding = true;
//	}
//}
//
//void godot::Door::_on_Area2D_area_exited(Node* other)
//{
//	if (other->get_parent()->get_name().find("Door") != -1)
//	{
//		correct_colliding = false;
//	}
//}
//
//godot::Door::Door()
//{
//	timer = Timer::_new();
//}
//
//godot::Door::~Door()
//{
//}
