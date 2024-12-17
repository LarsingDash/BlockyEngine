//
// Created by hmkam on 20/11/2024.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

class Circle : public Shape {
public:
    explicit Circle(float radius);
    ~Circle() override = default;

    PhysicsShape GetShape() override;

    [[nodiscard]] float GetRadius() const { return _radius; }

private:
    mutable float _radius;

    friend class PhysicsBody;
};

#endif //CIRCLE_HPP

