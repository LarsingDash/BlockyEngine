//
// Created by hmkam on 22/11/2024.
//

#include "MyContactListener.hpp"

#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

#include "PhysicsModule.hpp"
#include "components/physics/collision/CollisionHandler.hpp"

MyContactListener::MyContactListener(std::unordered_map<GameObject*, Body*>* gameObjectToBodyMap) {
    _gameObjectToBodyMap = gameObjectToBodyMap;
}

/// This is called after a contact is updated. This allows you to inspect a
/// contact before it goes to the solver. If you are careful, you can modify the
/// contact manifold (e.g. disable contact).
/// A copy of the old manifold is provided so that you can detect changes.
/// Note: this is called only for awake bodies.
/// Note: this is called even when the number of contact points is zero.
/// Note: this is not called for sensors.
/// Note: if you set the number of contact points to zero, you will not
/// get an EndContact callback. However, you may get a BeginContact callback
/// the next step.
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    auto body1 = contact->GetFixtureA()->GetBody();
    auto body2 = contact->GetFixtureB()->GetBody();

    GameObject* gameObject1 = nullptr;
    GameObject* gameObject2 = nullptr;

    for (auto [gameObject, body] : *_gameObjectToBodyMap) {
        if (body1 == body->b2body) {
            gameObject1 = gameObject;
        }
        if (body2 == body->b2body) {
            gameObject2 = gameObject;
        }
    }

    if (gameObject1 == nullptr || gameObject2 == nullptr) {
        std::cerr << "gameObject1 body does not exist, PreSolve" << std::endl;
        return;
    }

    //todo: check if for every game object if the colliding object isTrigger

    const auto handler1 = gameObject1->GetComponent<CollisionHandler>();
    if (handler1 != nullptr) {
        handler1->HandleCollision(gameObject1, gameObject2);
    }
    const auto handler2 = gameObject2->GetComponent<CollisionHandler>();
    if (handler2 != nullptr) {
        handler2->HandleCollision(gameObject1, gameObject2);
    }
}
