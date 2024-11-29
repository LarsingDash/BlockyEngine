//
// Created by hmkam on 19/11/2024.
//
#include "PhysicsShape.hpp"
#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

PhysicsShape::PhysicsShape(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic) :
	Component(gameObject, tag), isTrigger(isTrigger), isStatic(isStatic)
{
}

PhysicsShape::~PhysicsShape() = default;

void PhysicsShape::Start()
{
	// ModuleManager::getInstance().getModule<PhysicsModule>().AddCollider(*this);
	BLOCKY_ENGINE_DEBUG("Start todo: removed: " + this->tag) // todo:
}

void PhysicsShape::Update(float delta)
{
}

void PhysicsShape::End()
{
	// ModuleManager::getInstance().getModule<PhysicsModule>().RemoveCollider(*this); //todo:
}

void PhysicsShape::CollisionCallback(PhysicsShape& other)
{
}

