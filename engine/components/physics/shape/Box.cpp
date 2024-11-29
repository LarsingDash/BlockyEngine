//
// Created by hmkam on 19/11/2024.
//
#include "Box.hpp"

Box::Box(bool isTrigger, bool isStatic, float height, float width)
    : PhysicsShape(isTrigger, isStatic), _width(width), _height(height) {}

PhysicsType Box::GetType() {
    return PhysicsType::BOX;
}
