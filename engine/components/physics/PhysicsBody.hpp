//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <memory>

#include "components/Component.hpp"
#include "components/physics/shape/PhysicsShape.hpp"

class PhysicsBody : public Component {
public:
    explicit PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<PhysicsShape> physicsBody) :
        Component(gameObject, tag), _physicsShape(std::move(physicsBody)) {}

    ~PhysicsBody() override = default;

    void Start() override;
    void Update(float delta) override;
    void End() override;;
    virtual PhysicsType GetType();

    std::unique_ptr<PhysicsShape> _physicsShape;
};
#endif //PHYSICSBODY_HPP
