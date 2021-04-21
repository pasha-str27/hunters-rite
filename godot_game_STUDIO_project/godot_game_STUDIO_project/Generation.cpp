#include "Generation.h"
#include "CustomExtensions.h"

godot::Array godot::Generation::_get_rooms()
{
	return this->all_rooms_spawned;
}

void godot::Generation::InstanceAllRooms()
{
	for (int i = 0; i < all_rooms.size(); i++) {
		auto spawned = cast_to<PackedScene>(all_rooms[i])->instance();
		this->all_rooms_spawned.push_back(spawned);
	}

	closed_rooms = CustomExtensions::FindAll(all_rooms_spawned, [](Node* n) {
		Array arr = n->call("_get_directions");
		return arr.size() == 1;
	});
}

void godot::Generation::_register_methods()
{
	register_method((char*)"_ready", &Generation::_ready);
	register_method((char*)"_process", &Generation::_process);
	register_method((char*)"_input", &Generation::_input);
	register_method("_get_instance", &Generation::_get_instance);
	
	//	register property
	register_property<Generation, CrossedRoom*>("Crossed Room", &Generation::crossed_room, nullptr);
	register_property<Generation, Array>("All Rooms", &Generation::all_rooms, {});
	register_property<Generation, int>("Doors", &Generation::doorsCount, 0);
}

void godot::Generation::_init() {
	doorsCount = 5;
	Godot::print("init");

}

void godot::Generation::_ready()
{
	InstanceAllRooms();
	Array arr = cast_to<Node>(all_rooms_spawned[0])->call("_get_directions");
	Godot::print(String::num(arr.has("bottom")));
	//	console log
	Godot::print("Generation _ready");

	//OS::get_singleton()->set_window_fullscreen(true);

	int min = 32;
	crossed_room = get_node("CrossedRooms")->call("_get_instance");
	//crossed_room = cast_to<CrossedRoom>(node->get_script());
	if (crossed_room == nullptr) {
		Godot::print("crossed null");
		return;
	}

	//auto a = cast_to<PackedScene>(leftRooms[0])->instance();
	//add_child(a);


	////Godot::print(String::num_int64(dirs.size()));
	//Godot::print(String::num_int64(all_rooms.size()));
	//Array a = cast_to<Node>(all_rooms[0])->call("_get_directions");
	//Godot::print(String::num_int64(a.size()));
	//if (!cast_to<Ref<Object>>(arr[0])->is_null())
	//	Godot::print("booo");

	//Array arr = {};
	//for (int i = 0; i < crossed_room->left_rooms.size(); i++) {
	//	if (!cast_to<Array>(cast_to<Object>(crossed_room->left_rooms[i])->call("_get_directions"))->empty()) {
	//		arr.push_back(crossed_room->left_rooms[i]);
	//	}
	//}
	
	//Array arr1 = CustomExtensions::FindAll(all_rooms, [](Node* r) -> bool {
	//	Array a = r->call("_get_directions");
	//	return a.has("left");
	//});
	//
	//Godot::print( String::num_int64(arr1.size()));
	
	//Godot::print( String::num_int64(crossed_room->left_rooms.size()) );

	//if(crossed_room->left_rooms.empty())
	//	Godot::print(33);
	//auto r = crossed_room->get_script();
	//->call("_get_left_rooms");
	//Godot::print(r.back().get_type());
	//cast_to<Node2D>(get_node("/root/Node2D"));

}

void godot::Generation::_process(float delta)
{
}

void godot::Generation::_input(Variant ev) 
{
	Ref<InputEvent> _event = ev;
	if (_event->is_action_pressed("ui_cancel")) {
		_exit_tree();
	}
}

godot::Array godot::Generation::GetListByDirections(godot::Array dirs)
{
	return CustomExtensions::FindAll(all_rooms_spawned, [dirs](Node* n) {
		Array directions = n->call("_get_directions");
		for(int i = 0; i < dirs.size(); i++)
		{
			if (directions.has(dirs[i]))
				continue;

			return false;
		}
		return true;
	});
}

godot::Generation* godot::Generation::_get_instance()
{
	return this;
}

void godot::Generation::AddSpawnedRoom(Node *room)
{
	spawned_rooms.push_back(room);
}

godot::Generation::~Generation()
{
}

godot::Generation::Generation()
{
	Godot::print("constructor");
}

void godot::CrossedRoom::_register_methods()
{
	register_method("_get_instance", &CrossedRoom::_get_instance);

	register_property<CrossedRoom, Array>("Left rooms", &CrossedRoom::left_rooms, {});
	register_property<CrossedRoom, Array>("Top rooms", &CrossedRoom::top_rooms, {});
	register_property<CrossedRoom, Array>("Bottom rooms", &CrossedRoom::bottom_rooms, {});
	register_property<CrossedRoom, Array>("Right rooms", &CrossedRoom::right_rooms, {});
}

void godot::CrossedRoom::_init()
{
}


godot::CrossedRoom* godot::CrossedRoom::_get_instance()
{
	return this;
}

godot::CrossedRoom::CrossedRoom()
{

}


godot::CrossedRoom::~CrossedRoom()
{
}
