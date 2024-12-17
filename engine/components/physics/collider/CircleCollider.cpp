//
// Created by hmkam on 29/11/2024.
//

#include "CircleCollider.hpp"

#include <components/physics/shape/Circle.hpp>
#include <gameObject/GameObject.hpp>

CircleCollider::CircleCollider(GameObject* gameObject, const char* tag) : PhysicsBody(
	gameObject, tag, std::make_shared<Circle>(0), TypeProperties(COLLIDER, {}, {}, {},
	                                                             {}, {},
	                                                             {})) {}
