//
// Created by hmkam on 29/11/2024.
//

#include "BoxCollider.hpp"

#include <components/physics/shape/Box.hpp>
#include <gameObject/GameObject.hpp>

BoxCollider::BoxCollider(GameObject* gameObject, const char* tag) : PhysicsBody(
	gameObject, tag, std::make_shared<Box>(0, 0), TypeProperties(COLLIDER, {}, {}, {}, {}, {}, {})) {}
