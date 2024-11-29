//
// Created by hmkam on 28/11/2024.
//

#ifndef BOXRIGIDBODY_HPP
#define BOXRIGIDBODY_HPP

#include <components/physics/physicsShape/Box.hpp>

#include "RigidBody.hpp"

class BoxRigidBody : public RigidBody {
public:
    BoxRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                 float width): RigidBody(gameObject, tag,
                                         std::make_unique<Box>(isTrigger, isStatic, height, width)) {}

    PhysicsType GetType() override { return PhysicsType::BOX; };
};

#endif //BOXRIGIDBODY_HPP
