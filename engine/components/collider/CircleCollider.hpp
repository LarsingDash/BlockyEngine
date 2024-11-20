//
// Created by hmkam on 20/11/2024.
//

#ifndef CIRCLECOLLIDER_HPP
#define CIRCLECOLLIDER_HPP

#include "Collider.hpp"

class CircleCollider : public Collider
{
public:
    // explicit RectangleCollider(GameObject& gameObject);
    CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, float radius);
    ~CircleCollider() override = default;

private:
    float _radius;
};

#endif //CIRCLECOLLIDER_HPP

