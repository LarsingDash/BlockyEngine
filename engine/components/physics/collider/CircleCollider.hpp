//
// Created by hmkam on 29/11/2024.
//

#ifndef CIRCLECOLLIDER_HPP
#define CIRCLECOLLIDER_HPP
#include <components/physics/PhysicsBody.hpp>

class CircleCollider : public PhysicsBody {
public:
	CircleCollider(GameObject& gameObject, const char* tag);
	CircleCollider(GameObject& gameObject, const char* tag, float radius);
};
#endif //CIRCLECOLLIDER_HPP
