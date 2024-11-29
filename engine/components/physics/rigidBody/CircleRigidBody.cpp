//
// Created by hmkam on 28/11/2024.
//

#include "CircleRigidBody.hpp"

CircleRigidBody::CircleRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius,
                                 TypeProperties typeProperties) : RigidBody(
	gameObject, tag, std::make_unique<Circle>(isTrigger, isStatic, radius), typeProperties) {}
