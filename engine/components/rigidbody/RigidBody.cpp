//
// Created by hmkam on 25/11/2024.
//

#include "RigidBody.hpp"

#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

RigidBody::RigidBody(GameObject& gameObject, const char* tag, bool effectedByGravity, bool friction):
    Component(gameObject, tag), effectedByGravity(effectedByGravity), friction(friction)
{
}

void RigidBody::Start()
{
    ModuleManager::getInstance().getModule<PhysicsModule>().AddRigidBody(*this);
    BLOCKY_ENGINE_DEBUG("Start: " + this->tag)
}

void Collider::Update(float delta)
{
}

void RigidBody::End()
{
    ModuleManager::getInstance().getModule<PhysicsModule>().RemoveRigidBody(*this);
}

