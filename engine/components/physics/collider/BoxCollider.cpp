//
// Created by hmkam on 29/11/2024.
//

#include "BoxCollider.hpp"

#include <components/physics/shape/Box.hpp>

BoxCollider::BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                         float width) : PhysicsBody(gameObject, tag,
                                                    std::make_unique<Box>(height, width),
                                                    TypeProperties(COLLIDER, isTrigger, isStatic, {}, {},
                                                                   {}, {},
                                                                   {})) {}

