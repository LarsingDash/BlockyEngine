//
// Created by hmkam on 29/11/2024.
//

#include "CircleCollider.hpp"

#include <components/physics/shape/Circle.hpp>

CircleCollider::CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius) :
	PhysicsBody(gameObject, tag,
	            std::make_unique<Circle>(radius),
	            TypeProperties(COLLIDER, isTrigger, isStatic, {}, {},
	                           {}, {},
	                           {})) {}
