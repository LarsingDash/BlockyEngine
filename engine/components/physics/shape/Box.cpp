//
// Created by hmkam on 19/11/2024.
//
#include "Box.hpp"

#include <logging/BLogger.hpp>

Box::Box(bool isTrigger, bool isStatic, float height, float width)
    : PhysicsShape(isTrigger, isStatic), _width(width), _height(height) {
    BLOCKY_ENGINE_DEBUG_STREAM("Box::Box(): " << width << ", "<< height);
}

PhysicsType Box::GetType() {
    return PhysicsType::BOX;
}
