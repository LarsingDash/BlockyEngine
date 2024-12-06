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
		
		void Start() override;
		void Update(float delta) override;
		void End() override;
		
		void SetDirectionByAngle(float angle);
		
	private:
		Component* _clone(const GameObject& parent) override;
		
		glm::vec2 _direction;
		float _speed;
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_
