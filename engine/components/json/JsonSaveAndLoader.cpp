//
// Created by larsv on 01/01/2025.
//

#include "JsonSaveAndLoader.hpp"

#include <gameObject/GameObject.hpp>

JsonSaveAndLoader::JsonSaveAndLoader(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false){}

void JsonSaveAndLoader::Start() {}

void JsonSaveAndLoader::Update(float delta) {}

void JsonSaveAndLoader::End() {}

Component* JsonSaveAndLoader::_clone(const GameObject& parent) {
	auto clone = new JsonSaveAndLoader(*this);
	return clone;
}