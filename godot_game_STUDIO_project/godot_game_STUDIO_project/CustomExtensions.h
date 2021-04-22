#pragma once
#include <Array.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <Godot.hpp>
#include <RandomNumberGenerator.hpp>
#include <functional>

namespace godot {
	static class CustomExtensions
	{
	public:
		static Array FindAll(Array arr, const std::function<bool(Node*)>& isCorrect) {
			Array returned = {};
			for (int i = 0; i < arr.size(); i++) {
				auto a = arr[i];
				if (isCorrect(a))
					returned.push_back(a);
			}
			return returned;
		}

		static PackedScene* Find(Array arr, const std::function<bool(Node*)>& isCorrect) {
			Array returned = {};
			for (int i = 0; i < arr.size(); i++) {
				auto a = arr[i];
				if (isCorrect(a))
					return Object::cast_to<PackedScene>(a);
			}
			PackedScene* scene = PackedScene::_new();
			return scene;
		}

		static void AddRange(Array &addTo, Array &whatToAdd) {
			for (int i = 0; i < whatToAdd.size(); i++) {
				addTo.push_back(whatToAdd[i]);
			}
		}

		static Array GetComponentsInChildren(Node2D *_this, NodePath parent_node_name) {
			Array arr = _this->get_node(parent_node_name)->get_children();
			Array children_instances = {};
			for (int i = 0; i < arr.size(); i++) {
				auto instance = Object::cast_to<Node2D>(arr[i])->call("_get_instance");
				if(instance != nullptr)
					children_instances.push_back(instance);
			}
			return children_instances;
		}

	};
}



