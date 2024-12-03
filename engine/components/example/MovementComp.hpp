//
// Created by larsv on 29/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_

#include "components/Component.hpp"

class MovementComp : public Component {
	public:
		MovementComp(GameObject* gameObject, const char* tag);
		~MovementComp() override;
		
		Component* _cloneImpl(GameObject& parent) override;

		void Start() override;
		void Update(float delta) override;
		void End() override;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_
