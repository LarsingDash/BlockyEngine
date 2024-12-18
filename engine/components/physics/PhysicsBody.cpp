//
// Created by hmkam on 27/11/2024.
//

#include "PhysicsBody.hpp"

#include "gameObject/GameObject.hpp"
#include "logging/BLogger.hpp"
#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/physics/PhysicsModule.hpp"
#include "shape/Box.hpp"
#include "shape/Circle.hpp"

PhysicsBody::PhysicsBody(GameObject* gameObject, const char* tag, std::shared_ptr<Shape> physicsBody,
                         const TypeProperties& typeProperties) : Component(gameObject, tag, true),
                                                                 _physicsShape(std::move(physicsBody)),
                                                                 _typeProperties(
                                                                     std::make_shared<TypeProperties>(typeProperties)) {
    BLOCKY_ENGINE_DEBUG_STREAM("Address: " << this << " properties: "<< this->_typeProperties << ", Tag: " << tag);
}

void PhysicsBody::Start() {
    switch (_physicsShape->GetShape()) {
        case BOX: {
            const auto* const shape = dynamic_cast<Box*>(GetShapeReference().get());
            auto& scale = componentTransform->GetWorldScale();
            shape->_width = scale.x;
            shape->_height = scale.y;
            break;
        }
        case CIRCLE: {
            const auto* const shape = dynamic_cast<Circle*>(GetShapeReference().get());
            const float scale = (componentTransform->GetWorldScale().y + componentTransform->GetWorldScale().x) / 4;
            shape->_radius = scale;
            break;
        }
    }

    BLOCKY_ENGINE_DEBUG_STREAM("Address: " << this << " properties: "<< this->_typeProperties<< ", Tag: " << tag);
    ModuleManager::GetInstance().GetModule<PhysicsModule>().AddCollider(*this);
}

void PhysicsBody::Update(float delta) {}

void PhysicsBody::End() {
    ModuleManager::GetInstance().GetModule<PhysicsModule>().RemoveCollider(*this);
}

void PhysicsBody::SetOnEnter(const std::function<void(GameObject& other)>& callback) {
    enter = callback;
}

void PhysicsBody::SetOnExit(const std::function<void(GameObject& other)>& callback) {
    exit = callback;
}

std::shared_ptr<Shape>& PhysicsBody::GetShapeReference() { return _physicsShape; }
PhysicsShape PhysicsBody::GetShape() { return _physicsShape->GetShape(); }
std::shared_ptr<TypeProperties> PhysicsBody::GetTypeProperties() { return _typeProperties; }
TypeProperties PhysicsBody::GetTypeProperties() const { return *_typeProperties; }

Component* PhysicsBody::_clone(const GameObject& parent) {
    BLOCKY_ENGINE_DEBUG_STREAM("Address: " << this << " properties: "<< this->_typeProperties<< ", Tag: " << tag);
    auto clone = new PhysicsBody(*this);
    BLOCKY_ENGINE_DEBUG_STREAM("Address: " << clone << " properties: "<< clone->_typeProperties<< ", Tag: " << tag);
    return clone;
}
