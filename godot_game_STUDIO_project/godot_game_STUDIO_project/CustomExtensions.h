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
	};
}
