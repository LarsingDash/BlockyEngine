//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <memory>
#include "components/physicsShape/PhysicsShape.hpp"

//todo:
class PhysicsBody
{
    /**
    * @var physicsBody
    */
protected:
    std::unique_ptr<PhysicsShape> _physicsShape;

public:
    explicit PhysicsBody(std::unique_ptr<PhysicsShape> physicsBody) : _physicsShape(std::move(physicsBody))
    {
    }

    virtual ~PhysicsBody() = default;
    [[nodiscard]] virtual std::string Operation() const =0;

    PhysicsBody(PhysicsBody&& other) noexcept : _physicsShape(std::move(other._physicsShape))
    {
    }

    PhysicsBody& operator=(PhysicsBody&& other) noexcept
    {
        _physicsShape = std::move(other._physicsShape);
        return *this;
    }
};
#endif //PHYSICSBODY_HPP
