//
// Created by larsv on 01/01/2025.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONSAVEANDLOADER_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONSAVEANDLOADER_HPP_

#include <components/Component.hpp>

#include "utilities/JsonUtil.hpp"

class JsonSaveAndLoader : public Component {
	public:
		JsonSaveAndLoader(GameObject* gameObject, const char* tag,
						  const char* jsonPath, const char* instanceDir = "");
		~JsonSaveAndLoader() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;

		JSON_REGISTER_HEADER(JsonSaveAndLoader)

	private:
		std::string _jsonPath;
		std::string _instanceDir;
		std::string _instancePath{};

		GameObject* _instanceObject{nullptr};

		Component* _clone(const GameObject& parent) override;
};

JSON_REGISTER_COMPONENT(JsonSaveAndLoader)

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONSAVEANDLOADER_HPP_
