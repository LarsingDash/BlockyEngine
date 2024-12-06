//
// Created by hmkam on 28/11/2024.
//

#ifndef CIRCLERIGIDBODY_HPP
#define CIRCLERIGIDBODY_HPP

#include <components/physics/PhysicsBody.hpp>

class CircleRigidBody : public PhysicsBody {
public:
	CircleRigidBody(GameObject& gameObject, const char* tag, bool isStatic,
	                glm::vec2 velocity,
	                float rotationVelocity, float angularResistance, float linearResistance,
	                bool gravityEnabled);
	CircleRigidBody(GameObject& gameObject, const char* tag, const TypeProperties& properties);

	CircleRigidBody(GameObject& gameObject, const char* tag, bool isStatic,
	                glm::vec2 velocity,
	                float rotationVelocity, float angularResistance, float linearResistance,
	                bool gravityEnabled,
	                float radius);
	CircleRigidBody(GameObject& gameObject, const char* tag, const TypeProperties& properties, float radius);
};

#endif //CIRCLERIGIDBODY_HPP
