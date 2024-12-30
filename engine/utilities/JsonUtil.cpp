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

	child.transform->SetPosition(
			jsonObject.at("transform").at("position").at("x").get<float>(),
			jsonObject.at("transform").at("position").at("y").get<float>()
	);
	child.transform->SetRotation(jsonObject.at("transform").at("rotation").get<float>());
	child.transform->SetScale(
			jsonObject.at("transform").at("scale").at("x").get<float>(),
			jsonObject.at("transform").at("scale").at("y").get<float>()
	);
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
	auto& scale = transform.GetLocalScale();
	auto rotation = transform.GetLocalRotation();

	auto text = nlohmann::json{
			{"tag", gameObject.tag},
			{"transform", {
					{"position", {{"x", position.x}, {"y", position.y}}},
					{"rotation", rotation},
					{"scale", {{"x", scale.x}, {"y", scale.y}}}
			}}
	};
	file << text.dump(2);

	file.close();
}