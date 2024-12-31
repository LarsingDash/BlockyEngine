//
// Created by larsv on 30/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_

#include <string>

#include <json/json.hpp>

class GameObject;

namespace JsonUtil {
	void LoadFromFile(GameObject& recipient, const std::string& filePath);
	void LoadFromString(GameObject& recipient, const std::string& text);
	void _gameObjectFromJson(GameObject& recipient, const nlohmann::json& jsonObject);

	void SaveToFile(const GameObject& gameObject, const std::string& filePath);
	nlohmann::json _gameObjectToJson(const GameObject& gameObject);
}

#endif //BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
