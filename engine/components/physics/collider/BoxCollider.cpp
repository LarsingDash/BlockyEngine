//
// Created by hmkam on 29/11/2024.
//

#include "BoxCollider.hpp"

#include <components/physics/shape/Box.hpp>
#include <gameObject/GameObject.hpp>

BoxCollider::BoxCollider(GameObject* gameObject, const char* tag): BoxCollider(
	gameObject, tag, gameObject->transform->GetLocalScale().y, gameObject->transform->GetLocalScale().x) {}

BoxCollider::BoxCollider(GameObject* gameObject, const char* tag, float height, float width) : PhysicsBody(
	gameObject, tag, std::make_shared<Box>(height, width), TypeProperties(COLLIDER, {}, {}, {}, {}, {}, {})) {}
