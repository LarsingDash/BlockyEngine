//
// Created by hmkam on 27/11/2024.
//
#ifndef COLLIDERBODY_HPP
#define COLLIDERBODY_HPP

#include "components/physics/PhysicsBody.hpp"

class ColliderBody : public PhysicsBody {
public:
    explicit ColliderBody(GameObject& gameObject, const char* tag, std::unique_ptr<PhysicsShape> physicsBody);

    //todo:
    void Start() override {};
    void Update(float delta) override {};
    void End() override {};
};

#endif //COLLIDERBODY_HPP
