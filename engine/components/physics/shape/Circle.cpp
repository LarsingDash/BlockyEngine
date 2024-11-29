//
// Created by hmkam on 20/11/2024.
//
#include "Circle.hpp"

Circle::Circle(bool isTrigger, bool isStatic, float radius)
    : PhysicsShape(isTrigger, isStatic), _radius(radius) {}

PhysicsType Circle::GetType() {
    return PhysicsType::CIRCLE;
}
