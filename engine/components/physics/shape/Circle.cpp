//
// Created by hmkam on 20/11/2024.
//
#include "Circle.hpp"

Circle::Circle(bool isTrigger, bool isStatic, float radius)
    : Shape(isTrigger, isStatic), _radius(radius) {}

PhysicsShape Circle::GetShape() {
    return PhysicsShape::CIRCLE;
}
