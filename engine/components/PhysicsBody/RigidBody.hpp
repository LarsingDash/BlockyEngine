//
// Created by hmkam on 27/11/2024.
//
#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP
#include <components/physicsShape/Box.hpp>
#include <components/physicsShape/Circle.hpp>
#include "PhysicsBody.hpp"

//todo:
class RigidBody : public PhysicsBody
{
public:
    explicit RigidBody(std::unique_ptr<PhysicsShape> physicsBody) : PhysicsBody(std::move(physicsBody))
    {
    }

    [[nodiscard]] std::string Operation() const override
    {
        return "RigidBody operation: \n" + this->PhysicsBody::Operation();
    }
};

static RigidBody BoxRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                              float width)
{
    return RigidBody(std::make_unique<Box>(gameObject, tag, isTrigger, isStatic, height, width));
}

static RigidBody CircleRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius)
{
    return RigidBody(std::make_unique<Circle>(gameObject, tag, isTrigger, isStatic, radius));
}
#endif //RIGIDBODY_HPP
