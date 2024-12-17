//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include "gameObject/GameObject.hpp"
#include "logging/BLogger.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/physics/PhysicsModule.hpp"

#include <utility>
#include <iostream>

PhysicsBody::PhysicsBody(GameObject* gameObject, const char* tag, std::shared_ptr<Shape> physicsBody,
                         const TypeProperties& typeProperties) : Component(gameObject, tag, true),
                                                                 _physicsShape((std::move(physicsBody))),
                                                                 _typeProperties(
                                                                     typeProperties) {
}

void PhysicsBody::Start() {
    ModuleManager::GetInstance().GetModule<PhysicsModule>().AddCollider(*this);
}

void PhysicsBody::Update(float delta) {
}

void PhysicsBody::End() {
    ModuleManager::GetInstance().GetModule<PhysicsModule>().RemoveCollider(*this);
}

void PhysicsBody::SetOnEnter(const std::function<void(GameObject &other)> &callback) {
    enter = callback;
}

void PhysicsBody::SetOnExit(const std::function<void(GameObject &other)> &callback) {
    exit = callback;
}

std::shared_ptr<Shape>* PhysicsBody::GetShapeReference() { return &_physicsShape; }
PhysicsShape PhysicsBody::GetShape() { return _physicsShape->GetShape(); }
TypeProperties PhysicsBody::GetTypeProperties() const { return _typeProperties; }

Component* PhysicsBody::_clone(const GameObject& parent) {
    auto clone = new PhysicsBody(*this);
    return clone;
}