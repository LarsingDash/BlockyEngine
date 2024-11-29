//
// Created by hmkam on 27/11/2024.
//
#ifndef COLLIDERBODY_HPP
#define COLLIDERBODY_HPP
#include <components/physics/physicsShape/Box.hpp>
#include <components/physics/physicsShape/Circle.hpp>
#include "PhysicsBody.hpp"

class ColliderBody : public PhysicsBody {
public:
    explicit ColliderBody(GameObject& gameObject, const char* tag,
                          std::unique_ptr<PhysicsShape> physicsBody) : PhysicsBody(
        gameObject, tag, std::move(physicsBody)) {}

    //todo:
    void Start() override {};
    void Update(float delta) override {};
    void End() override {};
    PhysicsType GetType() override = 0;
};

class BoxCollider : public ColliderBody {
public:
    BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                float width): ColliderBody(gameObject, tag,
                                           std::make_unique<Box>(isTrigger, isStatic, height, width)) {}

    PhysicsType GetType() override { return PhysicsType::BOX; };
};

class CircleCollider : public ColliderBody {
public:
    CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius):
        ColliderBody(gameObject, tag, std::make_unique<Circle>(isTrigger, isStatic, radius)) {}

    PhysicsType GetType() override { return PhysicsType::CIRCLE; };
};
#endif //COLLIDERBODY_HPP
