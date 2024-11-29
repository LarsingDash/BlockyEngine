//
// Created by hmkam on 29/11/2024.
//

#include "CircleCollider.hpp"

CircleCollider::CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius,
                               TypeProperties typeProperties)
	: ColliderBody(gameObject, tag, std::make_unique<Circle>(isTrigger, isStatic, radius), typeProperties) {}

