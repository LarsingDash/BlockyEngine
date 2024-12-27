//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include "gameObject/GameObject.hpp"
#include "logging/BLogger.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/physics/PhysicsModule.hpp"
#include "shape/Shape.hpp"

PhysicsBody::PhysicsBody(GameObject* gameObject, const char* tag, const PhysicsShape shape,
                         const TypeProperties& typeProperties) : Component(gameObject, tag, true),
                                                                 _shape(shape),
                                                                 _typeProperties(
                                                                     std::make_shared<TypeProperties>(
                                                                         typeProperties)) {}

void PhysicsBody::Start() {
    ModuleManager::GetInstance().GetModule<PhysicsModule>().AddPhysicsBody(*this);
}

void PhysicsBody::Update(float delta) {}

void PhysicsBody::End() {
    ModuleManager::GetInstance().GetModule<PhysicsModule>().RemovePhysicsBody(*this);
}

void PhysicsBody::SetOnEnter(const std::function<void(GameObject& other)>& callback) {
    enter = callback;
}

void PhysicsBody::SetOnExit(const std::function<void(GameObject& other)>& callback) {
    exit = callback;
}

PhysicsShape PhysicsBody::GetShape() { return _shape; }
std::shared_ptr<TypeProperties> PhysicsBody::GetTypeProperties() { return _typeProperties; }
const TypeProperties& PhysicsBody::ReadTypeProperties() const { return *_typeProperties; }

Component* PhysicsBody::_clone(const GameObject& parent) {
    auto clone = new PhysicsBody(*this);
    return clone;
}
