//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <memory>
#include "components/physics/physicsShape/PhysicsShape.hpp"

//todo:
class PhysicsBody : public Component //todo:
{
    /**
    * @var physicsBody
    */
protected:
    std::unique_ptr<PhysicsShape> _physicsShape;

public:
    explicit PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<PhysicsShape> physicsBody) :
        Component(gameObject, tag), _physicsShape(std::move(physicsBody)) {}

    ~PhysicsBody() override = default;
    [[nodiscard]] virtual std::string Operation() const =0;

    PhysicsBody(GameObject& gameObject, const char* tag, PhysicsBody&& other) noexcept : Component(gameObject, tag),
        _physicsShape(std::move(other._physicsShape))
    //todo: needed
    {}

    //todo:
    void Start() override = 0;
    void Update(float delta) override = 0;
    void End() override = 0;

    PhysicsBody& operator=(PhysicsBody&& other) noexcept
    //todo: needed
    {
        _physicsShape = std::move(other._physicsShape);
        return *this;
    }
};
#endif //PHYSICSBODY_HPP
