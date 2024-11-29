//
// Created by hmkam on 27/11/2024.
//
#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP
#include <memory>
#include "components/Component.hpp"
#include "components/physics/physicsShape/PhysicsShape.hpp"

class PhysicsBody : public Component {
    /**
    * @var physicsBody
    */
public: //todo: protected:
    std::unique_ptr<PhysicsShape> _physicsShape;

public:
    explicit PhysicsBody(GameObject& gameObject, const char* tag, std::unique_ptr<PhysicsShape> physicsBody) :
        Component(gameObject, tag), _physicsShape(std::move(physicsBody)) {}

    ~PhysicsBody() override = default;

    void Start() override = 0;
    void Update(float delta) override = 0;
    void End() override = 0;
    virtual PhysicsType GetType() = 0;
    //todo:remove? //todo: use get and set, for override functionality
    bool isStatic{false};
};
#endif //PHYSICSBODY_HPP
