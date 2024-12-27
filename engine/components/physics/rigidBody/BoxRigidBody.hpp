//
// Created by hmkam on 28/11/2024.
//

#ifndef BOXRIGIDBODY_HPP
#define BOXRIGIDBODY_HPP

#include <components/physics/PhysicsBody.hpp>

class BoxRigidBody : public PhysicsBody {
public:
	BoxRigidBody(GameObject* gameObject, const char* tag, bool isStatic, glm::vec2 velocity,
	             float rotationVelocity, float angularResistance,
	             float linearResistance, bool gravityEnabled);
	BoxRigidBody(GameObject* gameObject, const char* tag, const TypeProperties& properties);
};

#endif //BOXRIGIDBODY_HPP
