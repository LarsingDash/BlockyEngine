//
// Created by hmkam on 19/11/2024.
//
#include "PhysicsShape.hpp"
#include <logging/BLogger.hpp>
#include <moduleManager/ModuleManager.hpp>
#include <moduleManager/modules/physics/PhysicsModule.hpp>

PhysicsShape::PhysicsShape(bool isTrigger, bool isStatic) :
	isTrigger(isTrigger), isStatic(isStatic) {}

PhysicsShape::~PhysicsShape() = default;

void PhysicsShape::CollisionCallback(PhysicsShape& other) {}

