//
// Created by larsv on 01/01/2025.
//

#include "JsonLoader.hpp"

#include <gameObject/GameObject.hpp>

JsonLoader::JsonLoader(GameObject* gameObject, const char* tag, const char* jsonPath) :
		Component(gameObject, tag, false), _jsonPath(jsonPath) {}

void JsonLoader::Start() {
	
}

void JsonLoader::Update(float delta) {}

void JsonLoader::End() {}

Component* JsonLoader::_clone(const GameObject& parent) {
	auto clone = new JsonLoader(*this);
	return clone;
}