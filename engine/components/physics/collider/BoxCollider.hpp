//
// Created by hmkam on 29/11/2024.
//

#ifndef BOXCOLLIDER_HPP
#define BOXCOLLIDER_HPP

#include "components/physics/PhysicsBody.hpp"

class BoxCollider : public PhysicsBody {
public:
	BoxCollider(GameObject* gameObject, const char* tag);
};

#endif //BOXCOLLIDER_HPP
