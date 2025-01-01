//
// Created by larsv on 03/12/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_ROTATIONCOMP_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_ROTATIONCOMP_HPP_

#include "components/Component.hpp"
#include "utilities/JsonUtil.hpp"

class RotationComp : public Component {
	public:
		RotationComp(GameObject* gameObject, const char* tag);
		~RotationComp() override;

		void Start() override;
		void Update(float delta) override;
		void End() override;

		JSON_REGISTER_HEADER_DEFAULTS(RotationComp);

	private:
		Component* _clone(const GameObject& parent) override;
};

JSON_REGISTER_COMPONENT(RotationComp);

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_EXAMPLE_ROTATIONCOMP_HPP_
