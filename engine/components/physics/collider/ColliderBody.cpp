//
// Created by hmkam on 27/11/2024.
//

#include "ColliderBody.hpp"

ColliderBody::ColliderBody(GameObject& gameObject, const char* tag, std::unique_ptr<Shape> physicsBody,
                           TypeProperties typeProperties) : PhysicsBody(gameObject, tag, std::move(physicsBody),
                                                                        typeProperties) {}
