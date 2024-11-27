//
// Created by hmkam on 19/11/2024.
//
#include "Box.hpp"
#include <gameObject/GameObject.hpp>

Box::Box(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
         float width)
    : PhysicsShape(gameObject, tag, isTrigger, isStatic), _width(width), _height(height)
{
}

PhysicsType Box::GetType()
{
    return PhysicsType::BOX;
}
