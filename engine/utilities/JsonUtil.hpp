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
	GameObject* LoadFromFile(GameObject& recipient, const std::string& filePath);
	GameObject* LoadFromString(GameObject& recipient, const std::string& text);
	GameObject* _gameObjectFromJson(GameObject& recipient, const nlohmann::json& json);

	//ToJson
	void SaveToFile(const GameObject& gameObject, const std::string& filePath);
	nlohmann::ordered_json _gameObjectToJson(const GameObject& gameObject);

	//Component Registrations
	struct jsonConfig {
		std::function<void(GameObject& recipient, const nlohmann::json& json)> FromJson;
		std::function<nlohmann::json(const Component& other)> ToJson;
	};
	extern std::unordered_map<std::string, jsonConfig>& GetComponentRegistrations();

//Registration Macros
//CUSTOM SOURCE
#define JSON_REGISTER_FROM(componentClass, customFromJson) \
    void componentClass::FromJson(GameObject& recipient, const nlohmann::json& json) { \
        auto& comp = recipient.AddComponent<componentClass>(json.at("tag").get<std::string>().c_str()); \
        \
        if (comp.componentTransform) { \
			auto& trans = *comp.componentTransform; \
			auto& transJson = json.at("compTransform"); \
	 		\
			trans.SetPosition( \
				std::stof(transJson.at("position").at("x").get<std::string>()), \
				std::stof(transJson.at("position").at("y").get<std::string>()) \
			); \
			trans.SetRotation( \
				std::stof(transJson.at("rotation").get<std::string>()) \
			); \
			trans.SetScale( \
				std::stof(transJson.at("scale").at("x").get<std::string>()), \
				std::stof(transJson.at("scale").at("y").get<std::string>()) \
			); \
		} \
        \
        customFromJson(json, comp); \
    }
#define JSON_REGISTER_FROM_CUSTOM_CONSTRUCTOR(componentClass, ...) \
    void componentClass::FromJson(GameObject& recipient, const nlohmann::json& json) { \
        auto& comp = recipient.AddComponent<componentClass>(json.at("tag").get<std::string>().c_str(), __VA_ARGS__); \
        \
       	if (comp.componentTransform) { \
			auto& trans = *comp.componentTransform; \
			auto& transJson = json.at("compTransform"); \
	 		\
			trans.SetPosition( \
				std::stof(transJson.at("position").at("x").get<std::string>()), \
				std::stof(transJson.at("position").at("y").get<std::string>()) \
			); \
			trans.SetRotation( \
				std::stof(transJson.at("rotation").get<std::string>()) \
			); \
			trans.SetScale( \
				std::stof(transJson.at("scale").at("x").get<std::string>()), \
				std::stof(transJson.at("scale").at("y").get<std::string>()) \
			); \
		} \
    }
#define JSON_REGISTER_TO(componentClass, customToJson) \
    nlohmann::json componentClass::ToJson(const componentClass& other) { \
        nlohmann::json json = { \
            {"tag", other.tag}, \
        };                                             \
		\
        if (other.componentTransform) { \
			auto& transform = *other.componentTransform; \
			auto& position = transform.GetLocalPosition(); \
			auto rotation = transform.GetLocalRotation(); \
			auto& scale = transform.GetLocalScale(); \
     		\
			nlohmann::json trans = { \
				{"position", {{"x", std::to_string(position.x)}, {"y", std::to_string(position.y)}}}, \
				{"rotation", std::to_string(-rotation)}, \
				{"scale", {{"x", std::to_string(scale.x)}, {"y", std::to_string(scale.y)}}} \
		}; \
		\
    	json["compTransform"] = trans; \
}                                               \
                                                       \
        customToJson(json, other); \
        return json; \
    }

//DEFAULT SOURCE, REDIRECTING TO CUSTOM
#define JSON_REGISTER_FROM_DEFAULT(componentClass) \
    JSON_REGISTER_FROM( \
        componentClass, \
        [](const nlohmann::json& json, componentClass& other){} \
    )
#define JSON_REGISTER_TO_DEFAULT(componentClass) \
    JSON_REGISTER_TO( \
        componentClass, \
        [](nlohmann::json& json, const componentClass& other){} \
    )

//HEADER
#define JSON_REGISTER_HEADER(componentClass) \
    static void FromJson(GameObject& recipient, const nlohmann::json& json); \
    static nlohmann::json ToJson(const componentClass& other);

//COMPONENT REGISTRATION
#define JSON_REGISTER_COMPONENT(componentClass) \
    static bool Register##componentClass = []() { \
        JsonUtil::GetComponentRegistrations()[typeid(componentClass).name()] = JsonUtil::jsonConfig{ \
            [](GameObject& recipient, const nlohmann::json& json) { \
                componentClass::FromJson(recipient, json); \
            }, \
            [](const Component& other) { \
                return componentClass::ToJson(reinterpret_cast<const componentClass&>(other)); \
            } \
        }; \
        return true; \
    }();
}

#endif //BLOCKYENGINE_ENGINE_UTILITIES_JSONUTIL_HPP_
