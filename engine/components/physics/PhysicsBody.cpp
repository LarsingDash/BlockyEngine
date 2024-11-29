//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

PhysicsBody::PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<Shape> physicsBody,
                         PhysicsType physicsType) : Component(gameObject, tag), physicsShape(std::move(physicsBody)),
                                                    //physicsType(physicsType),
                                                    lastPos(gameObject.transform->GetWorldPosition()),
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

PhysicsShape PhysicsBody::GetShape() { return physicsShape->GetShape(); }
PhysicsType PhysicsBody::GetType() { return PhysicsType::COLLIDER; } //physicsType->GetType(); } //todo:

void PhysicsBody::CollisionCallback(PhysicsBody& other) {
    BLOCKY_ENGINE_DEBUG_STREAM(
        "CollisionCallback()" << " tag: " << tag << " other.tag : " << other.tag);
}
