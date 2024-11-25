//
// Created by hmkam on 25/11/2024.
//

#include "RigidBody.hpp"

RigidBody::RigidBody(GameObject& gameObject, const char* tag, bool effectedByGravity, bool friction):
    Component(gameObject, tag), effectedByGravity(effectedByGravity), friction(friction)
{
}
