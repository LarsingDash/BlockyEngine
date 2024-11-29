//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

PhysicsBody::PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<PhysicsShape> physicsBody) :
    Component(gameObject, tag), physicsShape(std::move(physicsBody)), lastPos(gameObject.transform->GetWorldPosition()),
    lastRotation(gameObject.transform->GetWorldRotation()) {}

void PhysicsBody::Start() {
    ModuleManager::getInstance().getModule<PhysicsModule>().AddCollider(*this);
}

void PhysicsBody::Update(float delta) {
    lastPos = gameObject.transform->GetWorldPosition();
    lastRotation = gameObject.transform->GetWorldRotation();
};

void PhysicsBody::End() {
    ModuleManager::getInstance().getModule<PhysicsModule>().RemoveCollider(*this);
};

PhysicsType PhysicsBody::GetType() { return physicsShape->GetType(); }

void PhysicsBody::CollisionCallback(PhysicsBody& other) {
    BLOCKY_ENGINE_DEBUG_STREAM(
        "CollisionCallback()" << " tag: " << tag << " other.tag : " << other.tag);
}
