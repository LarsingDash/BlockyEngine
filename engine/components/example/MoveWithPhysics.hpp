//
// Created by doguk on 12/17/2024.
//

#ifndef MOVEWITHPHYSICS_HPP
#define MOVEWITHPHYSICS_HPP
#include <components/physics/PhysicsBody.hpp>

#include "components/Component.hpp"

class MoveWithPhysics : public Component {
public:
    MoveWithPhysics(GameObject* gameObject, const char* tag, PhysicsBody& body);
    ~MoveWithPhysics() override = default;

    MoveWithPhysics(const MoveWithPhysics& other) = default;

    void Start() override;
    void Update(float delta) override;
    void End() override;

private:
    Component* _clone(const GameObject& parent) override;

    std::shared_ptr<TypeProperties> _bodyType;
};

#endif //MOVEWITHPHYSICS_HPP
