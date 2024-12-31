//
// Created by larsv on 30/12/2024.
//

#include "JsonUtil.hpp"

#include <json/json.hpp>

#include <fstream>
#include <sstream>

#include "logging/BLogger.hpp"
#include "gameObject/GameObject.hpp"

void JsonUtil::LoadFromString(GameObject& recipient, const std::string& text) {
	nlohmann::json jsonObject = nlohmann::json::parse(text);

	auto& child = recipient.AddChild(jsonObject.at("tag").get<std::string>());

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
}

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

void JsonUtil::SaveToFile(GameObject& gameObject, const std::string& filePath) {
	std::ofstream file{filePath};

	auto& transform = *gameObject.transform;
	auto& position = transform.GetLocalPosition();
	auto rotation = transform.GetLocalRotation();
	auto& scale = transform.GetLocalScale();

	auto text = nlohmann::json{
			{"tag", gameObject.tag},
			{"transform", {
					{"position", {{"x", std::to_string(position.x)}, {"y", std::to_string(position.y)}}},
					{"rotation", std::to_string(rotation)},
					{"scale", {{"x", std::to_string(scale.x)}, {"y", std::to_string(scale.y)}}}
			}}
	};
	file << text.dump(2);

	file.close();
}