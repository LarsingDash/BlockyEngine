//
// Created by hmkam on 03/12/2024.
//

#include "CollisionHandler.hpp"

#include <utility>

CollisionHandler::CollisionHandler(GameObject& gameObject, const char* tag,
                                   std::function<void(GameObject*, GameObject*)> customCollisionHandler) :
	Component(gameObject, tag), _customCollisionHandler(std::move(customCollisionHandler)) {}

void CollisionHandler::HandleCollision(GameObject* obj1, GameObject* obj2) { _customCollisionHandler(obj1, obj2); }
