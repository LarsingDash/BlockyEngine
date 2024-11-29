//
// Created by hmkam on 19/11/2024.
//
#include "Shape.hpp"
#include <logging/BLogger.hpp>
// todo:
// #include <moduleManager/ModuleManager.hpp>
// #include <moduleManager/modules/physics/PhysicsModule.hpp>

Shape::Shape(bool isTrigger, bool isStatic) :
	isTrigger(isTrigger), isStatic(isStatic) {}

Shape::~Shape() = default;

void Shape::CollisionCallback(Shape& other) {
	BLOCKY_ENGINE_DEBUG_STREAM(
		"CollisionCallback()" << " GetType(): " << GetShape() << " other.GetType() : " << other.GetShape());
}

