//
// Created by hmkam on 20/11/2024.
//

#ifndef CIRCLECOLLIDER_HPP
#define CIRCLECOLLIDER_HPP

#include "PhysicsShape.hpp"

class Circle : public PhysicsShape {
public:
    Circle(bool isTrigger, bool isStatic, float radius);
    ~Circle() override = default;

    PhysicsType GetType() override;

    [[nodiscard]] float GetRadius() const { return _radius; }

private:
    float _radius;
};

#endif //CIRCLECOLLIDER_HPP

