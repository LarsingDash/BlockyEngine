//
// Created by doguk on 12/17/2024.
//

#include "MoveWithPhysics.hpp"

#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

MoveWithPhysics::MoveWithPhysics(GameObject* gameObject, const char* tag, PhysicsBody& body):
    Component(gameObject, tag), _bodyType(body.GetTypeProperties()) {
    BLOCKY_ENGINE_DEBUG_STREAM(
        "Address: " << &body << " properties: "<< body.GetTypeProperties()<<", Tag: " << body.tag);
}

void MoveWithPhysics::Start() {}

void MoveWithPhysics::Update(float delta) {
    static double i = 2;
    const auto direction = glm::vec2{delta * 10000, i};
    i = (i * 1.1);

    if (abs(i) > 10000) { i = -(i / 10000); }

    BLOCKY_ENGINE_DEBUG_STREAM(
        "Address: " << &_bodyType << ", xy velocity: " << _bodyType.get()->linearVelocity.x<<", "<< _bodyType.get()->
        linearVelocity.y);
    _bodyType->SetLinearVelocity(direction);
}

void MoveWithPhysics::End() {}

Component* MoveWithPhysics::_clone(const GameObject& parent) {
    return new MoveWithPhysics(*this);
}
