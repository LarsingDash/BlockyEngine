//
// Created by hmkam on 29/11/2024.
//

#ifndef BOXCOLLIDER_HPP
#define BOXCOLLIDER_HPP

#include "ColliderBody.hpp"

class BoxCollider : public ColliderBody {
public:
	BoxCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float height, float width,
	            TypeProperties typeProperties);
};

#endif //BOXCOLLIDER_HPP
