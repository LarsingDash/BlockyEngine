//
// Created by doguk on 12/17/2024.
//

#include "MoveWithPhysics.hpp"

#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

MoveWithPhysics::MoveWithPhysics(GameObject* gameObject, const char* tag, PhysicsBody& body):
    Component(gameObject, tag), _bodyType(body.GetTypeProperties()) {}

void MoveWithPhysics::Start() {}

void MoveWithPhysics::Update(float delta) {
    // Some movement pattern
    static double i = 2;
    const auto direction = glm::vec2{delta * 10000, i};
    i = (i * 1.1);
    if (abs(i) > 10000) { i = -(i / 10000); }

    _bodyType->SetLinearVelocity(direction);
}

void MoveWithPhysics::End() {}

Component* MoveWithPhysics::_clone(const GameObject& parent) {
    return new MoveWithPhysics(*this);
}
