#ifndef GODOT_CPP_CONCAVEPOLYGONSHAPE_HPP
#define GODOT_CPP_CONCAVEPOLYGONSHAPE_HPP


#include <gdnative_api_struct.gen.h>
#include <cstdint>

#include <core/CoreTypes.hpp>
#include <core/Ref.hpp>

#include "Shape.hpp"
namespace godot {


class ConcavePolygonShape : public Shape {
	struct ___method_bindings {
		godot_method_bind *mb_get_faces;
		godot_method_bind *mb_set_faces;
	};
	static ___method_bindings ___mb;
	static void *_detail_class_tag;

public:
	static void ___init_method_bindings();
	inline static size_t ___get_id() { return (size_t)_detail_class_tag; }

	static inline const char *___get_class_name() { return (const char *) "ConcavePolygonShape"; }
	static inline const char *___get_godot_class_name() { return (const char *) "ConcavePolygonShape"; }
	static inline Object *___get_from_variant(Variant a) { godot_object *o = (godot_object*) a; return (o) ? (Object *) godot::nativescript_1_1_api->godot_nativescript_get_instance_binding_data(godot::_RegisterState::language_index, o) : nullptr; }

	// enums

	// constants


	static ConcavePolygonShape *_new();

	// methods
	PoolVector3Array get_faces() const;
	void set_faces(const PoolVector3Array faces);

};

}

#endif