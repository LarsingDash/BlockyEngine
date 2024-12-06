//
// Created by hmkam on 20/11/2024.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

class Circle : public Shape {
public:
    Circle(float radius);
    ~Circle() override = default;

    PhysicsShape GetShape() override;

    [[nodiscard]] float GetRadius() const { return _radius; }

private:
    float _radius;
};

#endif //CIRCLE_HPP

