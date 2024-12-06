﻿//
// Created by larsv on 06/12/2024.
//

#include "components/Component.hpp"

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_SCENESWITCHCOMP_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_SCENESWITCHCOMP_HPP_

class SceneSwitchComp : public Component {
	public:
		SceneSwitchComp(GameObject* gameObject, const char* tag, const char* target);
		~SceneSwitchComp() override;

		Component* _cloneImpl(GameObject& parent) override;

		void Start() override;
		void Update(float delta) override;
		void End() override;
		
	private:
		std::string _target;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_SCENESWITCHCOMP_HPP_
