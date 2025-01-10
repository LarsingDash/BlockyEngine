//
// Created by larsv on 01/01/2025.
//

#include "JsonSaveAndLoader.hpp"

#include "gameObject/GameObject.hpp"

JsonSaveAndLoader::JsonSaveAndLoader(
		GameObject* gameObject, const char* tag,
		const char* jsonPath, const char* instanceDir) :
		Component(gameObject, tag, false),
		_jsonPath(jsonPath), _instanceDir(instanceDir) {}

void JsonSaveAndLoader::Start() {
	_instancePath = (std::filesystem::current_path() / _instanceDir / tag).string() + ".json";
	
	if (!std::filesystem::exists(_instancePath)) {
		std::filesystem::create_directories(std::filesystem::current_path() / _instanceDir);
		std::filesystem::copy_file(std::filesystem::absolute(_jsonPath), _instancePath);
	}

	_instanceObject = JsonUtil::LoadFromFile(*gameObject, _instancePath);
}

void JsonSaveAndLoader::Update(float delta) {}

void JsonSaveAndLoader::End() {
	JsonUtil::SaveToFile(*_instanceObject, _instancePath);
	_instanceObject->Destroy();
}

Component* JsonSaveAndLoader::_clone(const GameObject& parent) {
	auto clone = new JsonSaveAndLoader(*this);
	return clone;
}

JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(
		JsonSaveAndLoader,
		json.at("jsonPath").get<std::string>().c_str(),
		json.at("instanceDir").get<std::string>().c_str()
)

JSON_REGISTER_TO(
		JsonSaveAndLoader,
		[](nlohmann::json& json, const JsonSaveAndLoader& other) {
			json["jsonPath"] = other._jsonPath;
			json["instanceDir"] = other._instanceDir;
		}
)
