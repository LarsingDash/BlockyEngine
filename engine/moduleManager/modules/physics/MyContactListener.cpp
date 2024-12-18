//
// Created by hmkam on 22/11/2024.
//

#include "MyContactListener.hpp"

#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

#include "PhysicsModule.hpp"
#include "components/physics/collision/CollisionHandler.hpp"

MyContactListener::MyContactListener(std::unordered_map<PhysicsBody*, Body*>* gameObjectToBodyMap) {
    _gameObjectToBodyMap = gameObjectToBodyMap;
}

void MyContactListener::BeginContact(b2Contact* contact) {
    auto [gameObject1, gameObject2] = _gameObjects(contact);

    if (gameObject1 == nullptr || gameObject2 == nullptr) {
        BLOCKY_ENGINE_ERROR("gameObject does not exist, BeginContact");
        return;
    }

    const auto handler1 = gameObject1->GetComponent<CollisionHandler>();
    if (handler1 != nullptr) {
        handler1->_onEntryHandler(*gameObject2);
    }
    const auto handler2 = gameObject2->GetComponent<CollisionHandler>();
    if (handler2 != nullptr) {
        handler2->_onEntryHandler(*gameObject1);
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    auto [gameObject1, gameObject2] = _gameObjects(contact);

    if (gameObject1 == nullptr || gameObject2 == nullptr) {
        // when removing gameObject1 from PhysicsModule when in contact with other gameObject1 EndContact will be triggered
        //  after remove EndContact gets called and gameObject can't be found.
        // BLOCKY_ENGINE_ERROR("gameObject does not exist, EndContact");
        return;
    }

    const auto handler1 = gameObject1->GetComponent<CollisionHandler>();
    if (handler1 != nullptr) {
        handler1->_onExitHandler(*gameObject2);
    }
    const auto handler2 = gameObject2->GetComponent<CollisionHandler>();
    if (handler2 != nullptr) {
        handler2->_onExitHandler(*gameObject1);
    }
}

std::pair<GameObject*, GameObject*> MyContactListener::_gameObjects(b2Contact* contact) const {
    const auto body1 = contact->GetFixtureA()->GetBody();
    const auto body2 = contact->GetFixtureB()->GetBody();

    std::pair<GameObject*, GameObject*> gameObjects = std::make_pair(nullptr, nullptr);

    for (auto [physicsBody, body] : *_gameObjectToBodyMap) {
        if (body1 == body->b2body) {
            gameObjects.first = physicsBody->gameObject;
        }
        if (body2 == body->b2body) {
            gameObjects.second = physicsBody->gameObject;
        }
    }

    return gameObjects;
}
