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
                                         std::make_unique<Box>(gameObject, tag, isTrigger, isStatic, height, width))
    //todo, box and gameObject, tag, 2x meegegeven
    {}
};

#endif //BOXRIGIDBODY_HPP
