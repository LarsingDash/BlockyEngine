//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

void PhysicsBody::Start() {
    ModuleManager::getInstance().getModule<PhysicsModule>().AddCollider(*this);
}

void PhysicsBody::Update(float delta) {};

void PhysicsBody::End() {
    ModuleManager::getInstance().getModule<PhysicsModule>().RemoveCollider(*this);
};

PhysicsType PhysicsBody::GetType() { return _physicsShape->GetType(); }
