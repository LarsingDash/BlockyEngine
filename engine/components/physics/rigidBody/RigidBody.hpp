//
// Created by hmkam on 27/11/2024.
//
#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP
#include "components/physics/PhysicsBody.hpp"

class RigidBody : public PhysicsBody {
public:
	RigidBody(GameObject& gameObject, const char* tag, std::unique_ptr<Shape> physicsBody,
	          TypeProperties typeProperties);
};

#endif //RIGIDBODY_HPP

//todo: remove ridigbody and colliderbody
