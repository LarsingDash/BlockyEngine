//
// Created by larsv on 29/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_

#include "components/Component.hpp"

#include "utilities/JsonUtil.hpp"

class MovementComp : public Component {
	public:
		MovementComp(GameObject* gameObject, const char* tag, float distance = 15.f);
		~MovementComp() override;

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void SetDirectionByAngle(float angle);

		JSON_REGISTER_HEADER(MovementComp)

	private:
		Component* _clone(const GameObject& parent) override;

		glm::vec2 _direction;
		float _distance;
		float _speed;
};

JSON_REGISTER_COMPONENT(MovementComp)

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_PREFABS_MOVEMENTCOMP_HPP_
