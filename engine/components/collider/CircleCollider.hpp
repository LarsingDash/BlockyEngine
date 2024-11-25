//
// Created by hmkam on 20/11/2024.
//

#ifndef CIRCLECOLLIDER_HPP
#define CIRCLECOLLIDER_HPP

#include "Collider.hpp"

class CircleCollider : public Collider
{
public:
    CircleCollider(GameObject& gameObject, const char* tag, bool isTrigger, bool isStatic, float radius);
    ~CircleCollider() override = default;

    ColliderType GetColliderType() override;

    [[nodiscard]] float GetRadius() const { return _radius; }

private:
    float _radius;
};

#endif //CIRCLECOLLIDER_HPP

