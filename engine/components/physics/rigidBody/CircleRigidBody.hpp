//
// Created by hmkam on 28/11/2024.
//

#ifndef CIRCLERIGIDBODY_HPP
#define CIRCLERIGIDBODY_HPP

#include <components/physics/PhysicsBody.hpp>

class CircleRigidBody : public PhysicsBody {
public:
	CircleRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic,
	                glm::vec2 velocity,
	                float rotationVelocity, float angularResistance, float linearResistance,
	                bool gravityEnabled,
	                float radius);
};

#endif //CIRCLERIGIDBODY_HPP
