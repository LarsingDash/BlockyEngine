//
// Created by hmkam on 19/11/2024.
//

#include "Collider.hpp"

#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

Collider::Collider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic) :
	Component(gameObject, tag), isTrigger(isTrigger), isStatic(isStatic)
{
}

Collider::~Collider() = default;

void Collider::Start()
{
	ModuleManager::getInstance().getModule<PhysicsModule>().AddCollider(*this);
	BLOCKY_ENGINE_DEBUG("Start: " + this->tag)
}

void Collider::Update(float delta)
{
}

void Collider::End()
{
	ModuleManager::getInstance().getModule<PhysicsModule>().RemoveCollider(*this);
}

void Collider::CollisionCallback(Collider& other)
{
}

