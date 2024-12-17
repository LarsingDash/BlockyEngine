//
// Created by doguk on 12/17/2024.
//

#include "MoveWithPhysics.hpp"

#include <gameObject/GameObject.hpp>

MoveWithPhysics::MoveWithPhysics(GameObject* gameObject, const char* tag, PhysicsBody& body): Component(gameObject, tag), _body(std::make_unique<PhysicsBody>(body))
{
}

MoveWithPhysics::MoveWithPhysics(const MoveWithPhysics& other): Component(other.gameObject, other.tag.c_str()), _body(std::make_unique<PhysicsBody>(*other._body))
{
}

//NOTE: This is ugly never actually do this.
glm::vec2 direction;

void MoveWithPhysics::Start()
{
    direction = _body->GetTypeProperties().velocity;
    // _body = std::make_unique<PhysicsBody>(*gameObject->GetComponent<PhysicsBody>("BoxColl"));
}

void MoveWithPhysics::Update(float delta)
{
    direction += glm::vec2{delta * 1000, 0};
    _body->GetTypeProperties().SetVelocity(direction);
}

void MoveWithPhysics::End()
{

}

Component* MoveWithPhysics::_clone(const GameObject& parent)
{
    return new MoveWithPhysics(*this);
}