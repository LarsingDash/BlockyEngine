//
// Created by larsv on 30/12/2024.
//

#include "JsonUtil.hpp"

#include <fstream>
#include <sstream>

#include "logging/BLogger.hpp"
#include "gameObject/GameObject.hpp"

extern std::unordered_map<std::string, JsonUtil::jsonConfig>& JsonUtil::GetComponentRegistrations() {
	static std::unordered_map<std::string, JsonUtil::jsonConfig> componentRegistrations{};
	return componentRegistrations;
}

GameObject* JsonUtil::LoadFromFile(GameObject& recipient, const std::string& filePath) {
	std::ifstream file{filePath};
	std::stringstream text;

	if (!file.is_open() || !file.good()) {
		BLOCKY_ENGINE_ERROR_STREAM("Encountered an error while opening the file in LoadFromFile() at:\n" << filePath);
		return nullptr;
	}

	while (!file.eof()) {
		std::string line;
		file >> line;
		text << line;
	}

	return LoadFromString(recipient, text.str());
}

GameObject* JsonUtil::LoadFromString(GameObject& recipient, const std::string& text) {
	nlohmann::json jsonObject = nlohmann::json::parse(text);
	return _gameObjectFromJson(recipient, jsonObject);
}

GameObject* JsonUtil::_gameObjectFromJson(GameObject& recipient, const nlohmann::json& json) { // NOLINT(*-no-recursion)
	//GameObject
	auto& child = recipient.AddChild(json.at("tag").get<std::string>());

	//Transform
	try {
		child.transform->SetPosition(
				std::stof(json.at("transform").at("position").at("x").get<std::string>()),
				std::stof(json.at("transform").at("position").at("y").get<std::string>())
		);
		child.transform->SetRotation(
				std::stof(json.at("transform").at("rotation").get<std::string>())
		);
		child.transform->SetScale(
				std::stof(json.at("transform").at("scale").at("x").get<std::string>()),
				std::stof(json.at("transform").at("scale").at("y").get<std::string>())
		);
	} catch (const std::exception& e) {
		BLOCKY_ENGINE_ERROR("Encountered an error with stof while parsing transform data");
		return nullptr;
	}

	//Components
	for (const auto& [componentName, componentJson] : json.at("components").items()) {
		auto registration = GetComponentRegistrations().find(componentName);
		if (registration != GetComponentRegistrations().end())
			registration->second.FromJson(child, componentJson);
		else
			BLOCKY_ENGINE_WARNING_STREAM(
					"No JSON registration was found during FromJson for: "
							<< componentName
							<< ". View Blocky Engine's Readme for instructions on serializing components"
			);
	}

	//Children
	for (const auto& childJson : json.at("children")) {
		_gameObjectFromJson(child, childJson);
	}

	return &child;
}

void JsonUtil::SaveToFile(const GameObject& gameObject, const std::string& filePath) {
	std::ofstream file{filePath, std::ios::trunc};

	//ToJson
	auto text = _gameObjectToJson(gameObject);
	file << text.dump(4);

	file.close();
}

nlohmann::ordered_json JsonUtil::_gameObjectToJson(const GameObject& gameObject) { // NOLINT(*-no-recursion)
	//Prepare transform
	auto& transform = *gameObject.transform;
	auto& position = transform.GetLocalPosition();
	auto rotation = transform.GetLocalRotation();
	auto& scale = transform.GetLocalScale();

	//Prepare components
	auto componentList = nlohmann::ordered_json::object();
	for (const auto& [type, components] : gameObject.GetComponents()) {
		auto registration = GetComponentRegistrations().find(type.name());
		if (registration != GetComponentRegistrations().end())
			for (const auto& component : components) {
				componentList[type.name()] = registration->second.ToJson(*component);
			}
		else
			BLOCKY_ENGINE_WARNING_STREAM(
					"No JSON registration was found during ToJson for: "
							<< type.name()
							<< ". View Blocky Engine's Readme for instructions on serializing components"
			);
	}

	//Prepare children
	auto childList = nlohmann::ordered_json::array();
	for (const auto& child : gameObject.GetChildren()) {
		childList.push_back(_gameObjectToJson(*child));
	}

	//ToJson
	auto result = nlohmann::ordered_json{
			{"tag", gameObject.tag},
			{"transform", {
					{"position", {{"x", std::to_string(position.x)}, {"y", std::to_string(position.y)}}},
					{"rotation", std::to_string(-rotation)},
					{"scale", {{"x", std::to_string(scale.x)}, {"y", std::to_string(scale.y)}}}
			}},
			{"components", componentList},
			{"children", childList}
	};

	return result;
}
