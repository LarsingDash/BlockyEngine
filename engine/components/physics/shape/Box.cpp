//
// Created by hmkam on 19/11/2024.
//
#include "Box.hpp"

#include <logging/BLogger.hpp>

Box::Box(float height, float width)
    : Shape(), _width(width), _height(height) {}

PhysicsShape Box::GetShape() {
    return PhysicsShape::BOX;
}
