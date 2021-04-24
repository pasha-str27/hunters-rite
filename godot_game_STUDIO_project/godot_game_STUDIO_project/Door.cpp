#include "Door.h"

void godot::Door::_register_methods()
{
	register_method("_ready", &Door::_ready);
	register_method("_get_correct_colliding", &Door::_get_correct_colliding);
	register_method("_on_Area2D_area_entered", &Door::_on_Area2D_area_entered);
	register_method("_on_Area2D_area_exited", &Door::_on_Area2D_area_exited);

	register_property<Door, String>("Direction", &Door::direction, "");
}

void godot::Door::_init()
{
}

void godot::Door::_ready()
{
	room_ref = get_parent()->get_parent()->call("_get_instance");
}

bool godot::Door::_get_correct_colliding()
{
	return correct_colliding;
}

void godot::Door::_on_Area2D_area_entered(Node* other)
{
	if (other->get_name().find("Wall") != -1)
	{
		Godot::print("Collision door with wall: " + direction);
		get_parent()->get_parent()->call_deferred("_add_door_collision", direction, 1);
	}

	if (other->get_parent()->get_name().find("Door") != -1)
	{
		if (room_ref->closed_room)
		{
			correct_colliding = true;
		}
		//AddRoom room = collision.gameObject.transform.parent.parent.GetComponent<AddRoom>();
		//StartCoroutine(CheckIndivid(room));
	}
}

void godot::Door::_on_Area2D_area_exited(Node* other)
{
	if (other->get_name().find("Door") != -1)
	{
		if (room_ref->closed_room)
		{
			correct_colliding = false;
		}
	}
}
