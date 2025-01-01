//
// Created by larsv on 01/01/2025.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONSAVEANDLOADER_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONSAVEANDLOADER_HPP_

#include <components/Component.hpp>

class JsonSaveAndLoader : public Component {
	public:
		JsonSaveAndLoader(GameObject* gameObject, const char* tag);
		~JsonSaveAndLoader() override = default; //Optional

		void Start() override;
		void Update(float delta) override;
		void End() override;
		
	private:
		Component* _clone(const GameObject& parent) override;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_JSON_JSONSAVEANDLOADER_HPP_
