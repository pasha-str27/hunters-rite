#include "Generation.h"
#include "CustomExtensions.h"

godot::Array godot::Generation::_get_rooms()
{
	return this->all_rooms_spawned;
}

void godot::Generation::InstanceAllRooms()
{
	//if (all_rooms.size() == 0)
	//	return;

	//for (int i = 0; i < all_rooms.size(); i++) {
	//	auto spawned = cast_to<PackedScene>(all_rooms[i])->instance();
	//	this->all_rooms_spawned.push_back(spawned);
	//}

	//closed_rooms = CustomExtensions::FindAll(all_rooms_spawned, [](Node* n) {
	//	Array arr = n->call("_get_directions");
	//	return arr.size() == 1;
	//});
}

void godot::Generation::_register_methods()
{
	register_method((char*)"_ready", &Generation::_ready);
	register_method((char*)"_process", &Generation::_process);
	register_method((char*)"_input", &Generation::_input);
	register_method("_get_instance", &Generation::_get_instance);
	
	register_property<Generation, Array>("All Rooms", &Generation::all_rooms, {});
	register_property<Generation, Ref<PackedScene>>("Left Closed Room", &Generation::left_closed_room, nullptr);
	register_property<Generation, Ref<PackedScene>>("Right Closed Room", &Generation::right_closed_room, nullptr);
	register_property<Generation, Ref<PackedScene>>("Top Closed Room", &Generation::top_closed_room, nullptr);
	register_property<Generation, Ref<PackedScene>>("Bottom Closed Room", &Generation::bottom_closed_room, nullptr);
	register_property<Generation, Ref<PackedScene>>("Closed Room", &Generation::closed_room, nullptr);
	register_property<Generation, int>("Doors", &Generation::doorsCount, 0);
}

void godot::Generation::_init() {
	doorsCount = 5;
	Godot::print("init");
	all_rooms_spawned = all_rooms;
}

void godot::Generation::_ready()
{
	//	console log
	Godot::print("Generation _ready");
	//OS::get_singleton()->set_window_fullscreen(true);
	this->crossed_room = get_node("CrossedRooms")->call("_get_instance");
	InstanceAllRooms();
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
	return CustomExtensions::FindAll(all_rooms, [dirs](Node* n) {
		auto node = cast_to<PackedScene>(n)->instance();
		Array directions = node->call("_get_directions");
		node = nullptr;
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

godot::Ref<godot::PackedScene> godot::Generation::GetClosedRoomByDirection(String r)
{
	if (r == "right")
		return right_closed_room;
	if (r == "left")
		return left_closed_room;
	if (r == "top")
		return top_closed_room;
	if (r == "bottom")
		return bottom_closed_room;
	return nullptr;
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

godot::Array godot::CrossedRoom::GetListByDirection(String dir)
{
	if (dir == "left")
		return left_rooms ;
	else if (dir == "right")
		return right_rooms;
	else if (dir == "top")
		return top_rooms;
	else if(dir == "bottom")
		return bottom_rooms;

	return Array();
}

godot::CrossedRoom::CrossedRoom()
{

}

godot::CrossedRoom::~CrossedRoom()
{
}
