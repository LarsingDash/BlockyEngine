//
// Created by hmkam on 28/11/2024.
//

#ifndef CIRCLERIGIDBODY_HPP
#define CIRCLERIGIDBODY_HPP

#include <components/physics/shape/Circle.hpp>

#include "RigidBody.hpp"

class CircleRigidBody : public RigidBody {
public:
	CircleRigidBody(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius,
	                TypeProperties typeProperties);
};

#endif //CIRCLERIGIDBODY_HPP
