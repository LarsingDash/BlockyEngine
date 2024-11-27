//
// Created by hmkam on 20/11/2024.
//
#include "Circle.hpp"
#include <gameObject/GameObject.hpp>

Circle::Circle(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius)
    : PhysicsShape(gameObject, tag, isTrigger, isStatic), _radius(radius)
{
}

PhysicsType Circle::GetType()
{
    return PhysicsType::CIRCLE;
}
