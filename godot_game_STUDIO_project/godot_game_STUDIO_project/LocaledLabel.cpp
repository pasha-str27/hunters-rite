#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "headers.h"
#endif

#include <TranslationServer.hpp>
#include <CheckBox.hpp>

void godot::LocaledLabel::_register_methods()
{
	register_method("_ready", &LocaledLabel::_ready);

	register_property<LocaledLabel, String>("text_key", &LocaledLabel::text_key, "");
}

void godot::LocaledLabel::_init()
{
}

void godot::LocaledLabel::_ready()
{
	//set_text(TranslationServer::get_singleton()->translate(text_key));

	if (this->get_class() == "Label")
		set_text(TranslationServer::get_singleton()->translate(text_key));
	else if (this->get_class() == "CheckBox")
		cast_to<CheckBox>(this)->set_text(TranslationServer::get_singleton()->translate(text_key));
}

godot::LocaledLabel::LocaledLabel()
{
	text_key = "";
}

godot::LocaledLabel::~LocaledLabel()
{
}
