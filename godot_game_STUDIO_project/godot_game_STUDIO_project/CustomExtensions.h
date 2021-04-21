#pragma once
#include <Array.hpp>
#include <Node.hpp>
#include <Object.hpp>
#include <Godot.hpp>
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

		static void AddRange(Array &addTo, Array &whatToAdd) {
			for (int i = 0; i < whatToAdd.size(); i++) {
				addTo.push_back(whatToAdd[i]);
			}
		}

	};
}



