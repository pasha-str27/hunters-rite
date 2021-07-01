#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

namespace godot
{
	class CustomExtensions
	{
	public:
		static Array FindAll(Array arr, const std::function<bool(Node*)>& isCorrect)
		{
			Array returned = {};
			for (int i = 0; i < arr.size(); i++) 
			{
				auto a = arr[i];
				if (isCorrect(a))
					returned.push_back(a);
			}

			return returned;
		}

		static Array FindAll(Array arr, const std::function<bool(String)>& isCorrect)
		{
			Array returned = {};

			for (int i = 0; i < arr.size(); i++)
			{
				auto a = arr[i];
				if (isCorrect(a))
					returned.push_back(a);
			}

			return returned;
		}

		static PackedScene* Find(Array arr, const std::function<bool(Node*)>& isCorrect)
		{
			Array returned = {};
			for (int i = 0; i < arr.size(); i++) 
			{
				auto a = arr[i];
				if (isCorrect(a))
					return Object::cast_to<PackedScene>(a);
			}

			return nullptr;
		}

		static void AddRange(Array &addTo, Array &whatToAdd) 
		{
			for (int i = 0; i < whatToAdd.size(); i++) 
				addTo.push_back(whatToAdd[i]);
		}

		static Array GetComponentsInChildren(Node2D *_this, NodePath parent_node_name)
		{
			Array arr = _this->get_node(parent_node_name)->get_children();
			Array children_instances = {};

			for (int i = 0; i < arr.size(); i++) 
			{
				auto instance = Object::cast_to<Node2D>(arr[i])->call("_get_instance");

				if(instance != nullptr)
					children_instances.push_back(instance);
			}

			return children_instances;
		}

		//	return nullptr if no found
		static Node* GetChildByName(Node *parent, String child_name) 
		{
			Array children = parent->get_children();

			for (int i = 0; i < children.size(); i++)
				if (Object::cast_to<Node>(children[i])->get_name() == child_name) 
					return Object::cast_to<Node>(children[i]);

			return nullptr;
		}

		static bool IsOnlyOnePlayerAlive(Node *from)
		{
			return !from->has_node("/root/Node2D/Node/Player1") || !from->has_node("/root/Node2D/Node/Player2");
		}

		static Node* IsIncludedInChildrenWithName(Node* parent, String name)
		{
			Array children = parent->get_children();
			for (int i = 0; i < children.size(); i++)
				if (Object::cast_to<Node>(children[i])->get_name().find(name) != -1)
					return children[i];
			return nullptr;
		}

		static std::vector<Node2D*> GetChildrenByWordInName(Node2D* parent, String word)
		{
			std::vector<Node2D*> children = {};

			Array childs = parent->get_children();

			for (int i = 0; i < childs.size(); i++)
				if (Object::cast_to<Node>(childs[i])->get_name().find(word) != -1)
					children.push_back(childs[i]);

			return children;
		}

		static Node2D* GetChildByWordInName(Node2D* parent, String word)
		{
			Array childs = parent->get_children();

			for (int i = 0; i < childs.size(); i++)
				if (Object::cast_to<Node>(childs[i])->get_name().find(word) != -1)
					return childs[i];

			return nullptr;
		}

		static Array GetRoomsByType(Node* generation_node, String type)
		{
			Array result = {};
			Array r = generation_node->call("_get_rooms");
			Array p = generation_node->call("_get_rooms_positions");
			std::vector<int> ids = {};
			Array rooms = r[0];
			Array positions = p[0];
			for (int i = 0; i < rooms.size(); i++)
				if ((String)Object::cast_to<Node>(rooms[i])->call("_get_room_type") == type)
					ids.push_back(i);

			for(int i = 0; i < ids.size(); i++)
				result.push_back(positions[ids[i]]);

			Array wrapper = {};
			wrapper.push_back(result);
			return wrapper;
		}
	};
}
