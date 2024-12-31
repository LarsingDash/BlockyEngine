//
// Created by larsv on 30/12/2024.
//

#include "JsonUtil.hpp"

#include <fstream>
#include <sstream>

#include "logging/BLogger.hpp"
#include "gameObject/GameObject.hpp"

std::unordered_map<std::string, JsonUtil::jsonConfig> JsonUtil::_componentRegistrations{};

void JsonUtil::LoadFromFile(GameObject& recipient, const std::string& filePath) {
	std::ifstream file{filePath};
	std::stringstream text;

	if (!file.is_open() || !file.good()) {
		BLOCKY_ENGINE_ERROR_STREAM("Encountered an error while opening the file in LoadFromFile() at:\n" << filePath);
		return;
	}

	while (!file.eof()) {
		std::string line;
		file >> line;
		text << line;
	}

	LoadFromString(recipient, text.str());
}

void JsonUtil::LoadFromString(GameObject& recipient, const std::string& text) {
	nlohmann::json jsonObject = nlohmann::json::parse(text);
	_gameObjectFromJson(recipient, jsonObject);
}

void JsonUtil::_gameObjectFromJson(GameObject& recipient, const nlohmann::json& jsonObject) { // NOLINT(*-no-recursion)
	//GameObject
	auto& child = recipient.AddChild(jsonObject.at("tag").get<std::string>());

	//Transform
	try {
		child.transform->SetPosition(
				std::stof(jsonObject.at("transform").at("position").at("x").get<std::string>()),
				std::stof(jsonObject.at("transform").at("position").at("y").get<std::string>())
		);
		child.transform->SetRotation(
				std::stof(jsonObject.at("transform").at("rotation").get<std::string>())
		);
		child.transform->SetScale(
				std::stof(jsonObject.at("transform").at("scale").at("x").get<std::string>()),
				std::stof(jsonObject.at("transform").at("scale").at("y").get<std::string>())
		);
	} catch (const std::exception& e) {
		BLOCKY_ENGINE_ERROR("Encountered an error with stof while parsing transform data");
	}

	//Components
	for (const auto& [componentName, componentJson] : jsonObject.at("components").items()) {
		auto registration = _componentRegistrations.find(componentName);
		if (registration != _componentRegistrations.end())
			registration->second.FromJson(child, componentJson);
		else
			BLOCKY_ENGINE_WARNING_STREAM(
					"No JSON registration was found during FromJson for: "
							<< componentName
							<< ". View Blocky Engine's Readme for instructions on serializing components"
			);
	}

	//Children
	for (const auto& childJson : jsonObject.at("children")) {
		_gameObjectFromJson(child, childJson);
	}
}

void JsonUtil::SaveToFile(const GameObject& gameObject, const std::string& filePath) {
	std::ofstream file{filePath};

	//ToJson
	auto text = _gameObjectToJson(gameObject);
	file << text.dump(4);

	file.close();
}

nlohmann::json JsonUtil::_gameObjectToJson(const GameObject& gameObject) { // NOLINT(*-no-recursion)
	//Prepare transform
	auto& transform = *gameObject.transform;
	auto& position = transform.GetLocalPosition();
	auto rotation = transform.GetLocalRotation();
	auto& scale = transform.GetLocalScale();

	//Prepare components
	auto componentList = nlohmann::json::object();
	for (const auto& [type, component] : gameObject.GetComponents()) {
		auto registration = _componentRegistrations.find(type.name());
		if (registration != _componentRegistrations.end())
			componentList[type.name()] = registration->second.ToJson();
		else
			BLOCKY_ENGINE_WARNING_STREAM(
					"No JSON registration was found during ToJson for: "
							<< type.name()
							<< ". View Blocky Engine's Readme for instructions on serializing components"
			);
	}

	//Prepare children
	auto childList = nlohmann::json::array();
	for (const auto& child : gameObject.GetChildren()) {
		childList.push_back(_gameObjectToJson(*child));
	}

	//ToJson
	auto result = nlohmann::json{
			{"tag", gameObject.tag},
			{"transform", {
					{"position", {{"x", std::to_string(position.x)}, {"y", std::to_string(position.y)}}},
					{"rotation", std::to_string(rotation)},
					{"scale", {{"x", std::to_string(scale.x)}, {"y", std::to_string(scale.y)}}}
			}},
			{"components", componentList},
			{"children", childList}
	};

	return result;
}
