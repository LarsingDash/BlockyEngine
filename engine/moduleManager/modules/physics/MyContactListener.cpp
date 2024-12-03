//
// Created by hmkam on 22/11/2024.
//

#include "MyContactListener.hpp"

#include <gameObject/GameObject.hpp>
#include <logging/BLogger.hpp>

MyContactListener::MyContactListener(std::unordered_map<GameObject*, b2Body*>* gameObjectToBodyMap) {
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

    // todo: 2 way map
    for (auto [gameObject, body] : *_gameObjectToBodyMap) {
        if (body1 == body) {
            gameObject1 = gameObject;
        }
        if (body2 == body) {
            gameObject2 = gameObject;
        }
    }

    if (gameObject1 == nullptr || gameObject2 == nullptr) {
        std::cerr << "gameObject1 body does not exist, PreSolve" << std::endl;
        return;
    }

    //todo: multi PhysicsBody
    auto* physicsBody1 = gameObject1->GetComponent<PhysicsBody>();
    auto* physicsBody2 = gameObject2->GetComponent<PhysicsBody>();

    if (physicsBody1 == nullptr || physicsBody2 == nullptr) {
        std::cerr << "Physics body does not exist, PreSolve" << std::endl;
        return;
    }

    if (physicsBody1->GetTypeProperties().isTrigger) {
        physicsBody1->CollisionCallback(*physicsBody2);
    }

    if (physicsBody2->GetTypeProperties().isTrigger) {
        physicsBody2->CollisionCallback(*physicsBody1);
    }

    if (body1->GetPosition().y < 51) {
        contact->SetEnabled(false);
    }
}
