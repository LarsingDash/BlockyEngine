//
// Created by hmkam on 20/11/2024.
//

#include "CircleCollider.hpp"
#include <gameObject/GameObject.hpp>

CircleCollider::CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius)
    : Collider(gameObject, tag, isTrigger, isStatic), _radius(radius)
{
}

ColliderType CircleCollider::GetColliderType()
{
    return ColliderType::CIRCLE;
}
