//
// Created by larsv on 01/01/2025.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONLOADER_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONLOADER_HPP_

#include "components/Component.hpp"
#include "utilities/JsonUtil.hpp"

class JsonLoader : public Component {
	public:
		JsonLoader(GameObject* gameObject, const char* tag, const char* jsonPath);
		~JsonLoader() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;

		JSON_REGISTER_HEADER(JsonLoader)

	private:
		std::string _jsonPath;

		Component* _clone(const GameObject& parent) override;
};

JSON_REGISTER_COMPONENT(JsonLoader)

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONLOADER_HPP_
