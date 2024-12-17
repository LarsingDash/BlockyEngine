//
// Created by hmkam on 20/11/2024.
//
#include "Circle.hpp"

Circle::Circle(float radius)
    : Shape(), _radius(radius) {}

PhysicsShape Circle::GetShape() {
    return PhysicsShape::CIRCLE;
}