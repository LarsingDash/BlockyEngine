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
TypeProperties PhysicsBody::GetTypeProperties() const { return _typeProperties; }
glm::vec2 PhysicsBody::LastPosition() const { return _lastPosition; }
float PhysicsBody::LastRotation() const { return _lastRotation; }
bool PhysicsBody::InitDone() const { return _isInitialized; }

void PhysicsBody::LastPosition(glm::vec2 position) { _lastPosition = position; }
void PhysicsBody::LastRotation(float rotation) { _lastRotation = rotation; }
void PhysicsBody::InitDone(bool initialized) { _isInitialized = initialized; }

void PhysicsBody::CollisionCallback(PhysicsBody& other) {
    //todo: implement collision callback interface
    BLOCKY_ENGINE_DEBUG_STREAM(
        "CollisionCallback()" << " tag: " << tag << " other.tag : " << other.tag);
}
