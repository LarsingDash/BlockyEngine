//
// Created by hmkam on 29/11/2024.
//

#include "CircleCollider.hpp"

#include <components/physics/shape/Circle.hpp>
#include <gameObject/GameObject.hpp>

CircleCollider::CircleCollider(GameObject* gameObject, const char* tag) : CircleCollider(
	gameObject, tag, (gameObject->transform->GetWorldScale().y + gameObject->transform->GetWorldScale().x) / 4) {}

CircleCollider::CircleCollider(GameObject* gameObject, const char* tag, float radius) : PhysicsBody(
	gameObject, tag, std::make_shared<Circle>(radius), TypeProperties(COLLIDER, {}, {}, {},
	                                                                  {}, {},
	                                                                  {})) {}