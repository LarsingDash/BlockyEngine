//
// Created by hmkam on 29/11/2024.
//

#include "BoxCollider.hpp"

#include "components/physics/shape/Shape.hpp"
#include "gameObject/GameObject.hpp"

BoxCollider::BoxCollider(GameObject* gameObject, const char* tag) : PhysicsBody(
	gameObject, tag, BOX, TypeProperties(COLLIDER, {}, {}, {}, {}, {}, {})) {}
