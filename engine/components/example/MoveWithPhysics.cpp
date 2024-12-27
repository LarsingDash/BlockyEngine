//
// Created by doguk on 12/17/2024.
//

#include "MoveWithPhysics.hpp"

#include <bits/random.h>
#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

MoveWithPhysics::MoveWithPhysics(GameObject* gameObject, const char* tag, PhysicsBody& body):
    Component(gameObject, tag), _bodyType(body.GetTypeProperties()) {}

void MoveWithPhysics::Start() {}

void MoveWithPhysics::Update(float delta) {
    // Some movement pattern
    static int i = 10;

    const auto direction = glm::vec2{delta * 10000, i};
    i = (i * 1.1);
    if (abs(i) > 10000) { i = -(i / 1000); }

    _bodyType->SetLinearVelocity(direction);
    _bodyType->rotationVelocity = delta * 100;
}

void MoveWithPhysics::End() {}

Component* MoveWithPhysics::_clone(const GameObject& parent) {
    return new MoveWithPhysics(*this);
}
