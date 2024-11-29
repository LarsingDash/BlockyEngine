//
// Created by hmkam on 29/11/2024.
//

#ifndef CIRCLECOLLIDER_HPP
#define CIRCLECOLLIDER_HPP
#include "components/physics/shape/Circle.hpp"

#include "ColliderBody.hpp"

class CircleCollider : public ColliderBody {
public:
	CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius,
	               TypeProperties typeProperties);
};
#endif //CIRCLECOLLIDER_HPP
