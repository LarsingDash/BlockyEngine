//
// Created by hmkam on 19/11/2024.
//

#include "BoxCollider.hpp"
#include <gameObject/GameObject.hpp>

BoxCollider::BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                         float width)
    : Collider(gameObject, tag, isTrigger, isStatic), _width(width), _height(height)
{
}

PhysicsType BoxCollider::GetType()
{
    return PhysicsType::BOX;
}
