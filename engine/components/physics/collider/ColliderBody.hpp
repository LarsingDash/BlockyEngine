//
// Created by hmkam on 27/11/2024.
//
#ifndef COLLIDERBODY_HPP
#define COLLIDERBODY_HPP

#include "components/physics/PhysicsBody.hpp"

class ColliderBody : public PhysicsBody {
public:
	ColliderBody(GameObject& gameObject, const char* tag, std::unique_ptr<Shape> physicsBody,
	             TypeProperties typeProperties);
};

#endif //COLLIDERBODY_HPP
