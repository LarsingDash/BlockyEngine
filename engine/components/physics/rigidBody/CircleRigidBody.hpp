//
// Created by hmkam on 28/11/2024.
//

#ifndef CIRCLERIGIDBODY_HPP
#define CIRCLERIGIDBODY_HPP

#include <components/physics/physicsShape/Circle.hpp>

#include "RigidBody.hpp"

class CircleRigidBody : public RigidBody {
public:
    CircleRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius):
        RigidBody(gameObject, tag, std::make_unique<Circle>(gameObject, tag, isTrigger, isStatic, radius)) {}
};

#endif //CIRCLERIGIDBODY_HPP
