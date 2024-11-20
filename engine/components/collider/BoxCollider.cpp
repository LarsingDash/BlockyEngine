//
// Created by hmkam on 19/11/2024.
//

#include "BoxCollider.hpp"
#include <gameObject/GameObject.hpp>

BoxCollider::BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, float height, float width)
    : Collider(gameObject, tag, ColliderType::BOX, isTrigger), _height(height), _width(width)
{
}
