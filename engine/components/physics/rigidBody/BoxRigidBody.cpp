//
// Created by hmkam on 28/11/2024.
//

#include "BoxRigidBody.hpp"

BoxRigidBody::BoxRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height,
                           float width, TypeProperties typeProperties) : RigidBody(gameObject, tag,
	std::make_unique<Box>(isTrigger, isStatic, height, width), typeProperties) {}
