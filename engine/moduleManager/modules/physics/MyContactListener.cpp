//
// Created by hmkam on 22/11/2024.
//

#include "MyContactListener.hpp"

#include <logging/BLogger.hpp>

MyContactListener::MyContactListener(std::unordered_map<Collider*, b2Body*>* colliderToBodyMap)
{
    _colliderToBodyMap = colliderToBodyMap;
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
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    auto body1 = contact->GetFixtureA()->GetBody();
    auto body2 = contact->GetFixtureB()->GetBody();

    Collider* collider1 = nullptr;
    Collider* collider2 = nullptr;

    // todo: 2 way map
    for (auto [collider, body] : *_colliderToBodyMap)
    {
        if (body1 == body)
        {
            collider1 = collider;
        }
        if (body2 == body)
        {
            collider2 = collider;
        }
    }

    if (collider1 != nullptr && collider2 != nullptr && collider1->isTrigger)
    {
        collider1->CollisionCallback(*collider2);
        collider2->CollisionCallback(*collider1);
    }

    if (body1->GetPosition().y < 51)
    {
        contact->SetEnabled(false);
    }
}
