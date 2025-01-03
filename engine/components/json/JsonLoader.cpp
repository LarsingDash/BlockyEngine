//
// Created by larsv on 01/01/2025.
//

#include "JsonLoader.hpp"

#include "gameObject/GameObject.hpp"

JsonLoader::JsonLoader(GameObject* gameObject, const char* tag, const char* jsonPath) :
		Component(gameObject, tag, false), _jsonPath(jsonPath) {}

void JsonLoader::Start() {
	JsonUtil::LoadFromFile(*gameObject, _jsonPath);
}

void JsonLoader::Update(float delta) {}

void JsonLoader::End() {}

Component* JsonLoader::_clone(const GameObject& parent) {
	auto clone = new JsonLoader(*this);
	return clone;
}

JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(
		JsonLoader,
		json.at("path").get<std::string>().c_str()
)

JSON_REGISTER_TO(
		JsonLoader,
		[](nlohmann::json& json, const JsonLoader& other) {
			json["path"] = other._jsonPath;
		}
)
