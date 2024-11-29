//
// Created by hmkam on 28/11/2024.
//

#ifndef BOXRIGIDBODY_HPP
#define BOXRIGIDBODY_HPP

#include <components/physics/shape/Box.hpp>

#include "RigidBody.hpp"

class BoxRigidBody : public RigidBody {
public:
    BoxRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height, float width);
};

#endif //BOXRIGIDBODY_HPP
