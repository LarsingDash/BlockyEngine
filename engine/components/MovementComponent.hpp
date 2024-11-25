//
// Created by larsv on 22/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_MOVEMENTCOMPONENT_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_MOVEMENTCOMPONENT_HPP_

#include "components/Component.hpp"

class MovementComponent : public Component {
	public:
		MovementComponent(GameObject& gameObject, const char* tag);
		~MovementComponent() override;

		void Start() override;
		void Update(float delta) override;
		void End() override;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_MOVEMENTCOMPONENT_HPP_
