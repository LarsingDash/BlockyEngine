//
// Created by hmkam on 19/11/2024.
//

#include "RectangleCollider.hpp"
#include <gameObject/GameObject.hpp>

RectangleCollider::RectangleCollider(GameObject& gameObject, const char* tag, bool isTrigger)
    : Collider(gameObject, tag, ColliderType::RECTANGLE, isTrigger), _width(0), _height(0)
{
    // //todo: use with height
    // _width = gameObject.transform->position.x;
    // _height = gameObject.transform->position.y;
}
