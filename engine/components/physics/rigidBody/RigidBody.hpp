//
// Created by hmkam on 27/11/2024.
//
#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP
#include "components/physics/PhysicsBody.hpp"

class RigidBody : public PhysicsBody {
public:
    explicit RigidBody(GameObject& gameObject, const char* tag,
                       std::unique_ptr<PhysicsShape> physicsBody) : PhysicsBody(
        gameObject, tag, std::move(physicsBody)) {}

    //todo:
    void Start() override {};
    void Update(float delta) override {};
    void End() override {};
};

#endif //RIGIDBODY_HPP