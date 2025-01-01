//
// Created by larsv on 30/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
#define BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_

#include <string>

#include <json/json.hpp>

class GameObject;
class Component;

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
		std::function<nlohmann::json(const Component& other)> ToJson;
	};
	extern std::unordered_map<std::string, jsonConfig>& GetComponentRegistrations();

//Registration Macros
#define JSON_REGISTER_SOURCE_DEFAULTS(componentClass) \
void componentClass::FromJson(GameObject& recipient, const nlohmann::json& jsonObject) { \
    recipient.AddComponent<componentClass>(jsonObject.at("tag").get<std::string>().c_str()); \
} \
nlohmann::json componentClass::ToJson(const componentClass& other) { \
    return nlohmann::json{{"tag", other.tag}}; \
}

#define JSON_REGISTER_HEADER_DEFAULTS(componentClass) \
    static void FromJson(GameObject& recipient, const nlohmann::json& jsonObject); \
    static nlohmann::json ToJson(const componentClass& other);

#define JSON_REGISTER_COMPONENT(componentClass) \
    static bool Register##componentClass = []() { \
        JsonUtil::GetComponentRegistrations()[typeid(componentClass).name()] = JsonUtil::jsonConfig{ \
            [](GameObject& recipient, const nlohmann::json& jsonObject) { \
                componentClass::FromJson(recipient, jsonObject); \
            }, \
            [](const Component& other) { \
                return componentClass::ToJson(reinterpret_cast<const componentClass&>(other)); \
            } \
        }; \
        return true; \
    }();
}

#endif //BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
