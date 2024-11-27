//
// Created by hmkam on 27/11/2024.
//
#ifndef COLLIDERBODY_HPP
#define COLLIDERBODY_HPP
#include <components/physicsShape/Box.hpp>
#include <components/physicsShape/Circle.hpp>
#include "PhysicsBody.hpp"

class ColliderBody : public PhysicsBody
{
public:
    explicit ColliderBody(std::unique_ptr<PhysicsShape> physicsBody) : PhysicsBody(std::move(physicsBody))
    {
    }

    [[nodiscard]] std::string Operation() const override
    {
        return "RigidBody operation: \n" + this->PhysicsBody::Operation();
    }
};

static ColliderBody BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                                float width)
{
    return ColliderBody(std::make_unique<Box>(gameObject, tag, isTrigger, isStatic, height, width));
}

static ColliderBody CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius)
{
    return ColliderBody(std::make_unique<Circle>(gameObject, tag, isTrigger, isStatic, radius));
}
#endif //COLLIDERBODY_HPP
