//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

PhysicsBody::PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<Shape> physicsBody,
                         const TypeProperties& typeProperties) : Component(gameObject, tag),
                                                                 _physicsShape(std::move(physicsBody)),
                                                                 _typeProperties(
                                                                     typeProperties),
                                                                 _lastPosition(
                                                                     gameObject.transform->
                                                                     GetWorldPosition()),
                                                                 _lastRotation(
                                                                     gameObject.transform->
                                                                     GetWorldRotation()) {}

void PhysicsBody::Start() {
    ModuleManager::getInstance().getModule<PhysicsModule>().AddCollider(*this);
}

void PhysicsBody::Update(float delta) {
    _lastPosition = gameObject.transform->GetWorldPosition();
    _lastRotation = gameObject.transform->GetWorldRotation();
};

void PhysicsBody::End() {
    ModuleManager::getInstance().getModule<PhysicsModule>().RemoveCollider(*this);
};

std::unique_ptr<Shape>* PhysicsBody::GetShapeReference() { return &_physicsShape; }
PhysicsShape PhysicsBody::GetShape() { return _physicsShape->GetShape(); }
TypeProperties PhysicsBody::GetTypeProperties() { return _typeProperties; }
glm::vec2 PhysicsBody::GetLastPosition() { return _lastPosition; }
float PhysicsBody::GetLastRotation() { return _lastRotation; }

void PhysicsBody::CollisionCallback(PhysicsBody& other) {
    BLOCKY_ENGINE_DEBUG_STREAM(
        "CollisionCallback()" << " tag: " << tag << " other.tag : " << other.tag);
}
