//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <memory>
#include <gameObject/GameObject.hpp>

#include "components/Component.hpp"
#include "components/physics/shape/Shape.hpp"
#include "type/Type.hpp"

class PhysicsBody : public Component {
public:
    PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<Shape> physicsBody, PhysicsType physicsType);
    ~PhysicsBody() override = default;

    void Start() override;
    void Update(float delta) override;
    void End() override;;
    virtual PhysicsShape GetShape();
    virtual PhysicsType GetType();
    void CollisionCallback(PhysicsBody& other); //todo: implement

    std::unique_ptr<Shape> physicsShape;
    std::unique_ptr<PhysicsType> physicsType;
    glm::vec2 lastPos;
    float lastRotation{};
};
#endif //PHYSICSBODY_HPP
