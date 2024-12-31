//
// Created by larsv on 30/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_

#include <string>

#include <json/json.hpp>

class GameObject;

namespace JsonUtil {
	//FromJson
	void LoadFromFile(GameObject& recipient, const std::string& filePath);
	void LoadFromString(GameObject& recipient, const std::string& text);
	void _gameObjectFromJson(GameObject& recipient, const nlohmann::json& jsonObject);

	//ToJson
	void SaveToFile(const GameObject& gameObject, const std::string& filePath);
	nlohmann::json _gameObjectToJson(const GameObject& gameObject);

	//Component Registrations
	struct jsonConfig {
		std::function<void(GameObject& recipient, const nlohmann::json& jsonObject)> FromJson;
		std::function<nlohmann::json()> ToJson;
	};
	extern std::unordered_map<std::string, jsonConfig> _componentRegistrations;

//Registration Macros
#define JSON_REGISTER_SOURCE_DEFAULTS(componentClass) \
void componentClass::FromJson(GameObject& recipient, const nlohmann::json& jsonObject) { \
	recipient.AddComponent<componentClass>(jsonObject.at("tag").get<std::string>().c_str()); \
} \
nlohmann::json componentClass::ToJson() { \
	return nlohmann::json{{"tag", tag}}; \
}

#define JSON_REGISTER_HEADER_DEFAULTS() \
	static void FromJson(GameObject& recipient, const nlohmann::json& jsonObject); \
	nlohmann::json ToJson();

#define JSON_REGISTER_COMPONENT(componentClass) \
	bool Register##componentClass = [this]() { \
    	JsonUtil::_componentRegistrations[typeid(componentClass).name()] = JsonUtil::jsonConfig{ \
			[](GameObject& recipient, const nlohmann::json& jsonObject) { \
				FromJson(recipient, jsonObject); \
			}, \
			[this]() { \
				return ToJson(); \
			} \
		}; \
		return true; \
	}();
}

#endif //BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
