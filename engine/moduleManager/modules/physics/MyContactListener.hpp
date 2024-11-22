// //
// // Created by hmkam on 22/11/2024.
// //
//
// #ifndef MYCONTACTLISTENER_HPP
// #define MYCONTACTLISTENER_HPP
// #include <unordered_map>
// #include <box2d/b2_contact.h>
// #include <box2d/b2_world_callbacks.h>
// #include <components/collider/Collider.hpp>
// #include <logging/BLogger.hpp>
//
// #include "PhysicsModule.hpp"
//
// //todo: move
// class MyContactListener : public b2ContactListener
// {
// public:
//     /// This is called after a contact is updated. This allows you to inspect a
//     /// contact before it goes to the solver. If you are careful, you can modify the
//     /// contact manifold (e.g. disable contact).
//     /// A copy of the old manifold is provided so that you can detect changes.
//     /// Note: this is called only for awake bodies.
//     /// Note: this is called even when the number of contact points is zero.
//     /// Note: this is not called for sensors.
//     /// Note: if you set the number of contact points to zero, you will not
//     /// get an EndContact callback. However, you may get a BeginContact callback
//     /// the next step.
//     void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
//     {
//         BLOCKY_ENGINE_DEBUG("PreSolve")
//
//         auto body1 = contact->GetFixtureA()->GetBody();
//         auto body2 = contact->GetFixtureB()->GetBody();
//
//         std::cout << "PreSolve!" << body1->GetPosition().y << ", " << body2->GetPosition().y << std::endl;
//
//         std::unordered_map<Collider*, b2Body*> _colliderToBodyMap; //todo:
//
//         Collider* collider1 = nullptr;
//         Collider* collider2 = nullptr;
//
//         // todo: 2 way map
//         for (auto [collider, body] : _colliderToBodyMap)
//         {
//             if (body1 == body)
//             {
//                 collider1 = collider;
//             }
//             if (body2 == body)
//             {
//                 collider2 = collider;
//             }
//         }
//
//         if (collider1 != nullptr && collider1->isTrigger)
//         {
//             //todo:			collider1.DoTrigger(&collider2)
//             collider1->SetTriggerEnterCallback();
//         }
//         if (collider2 != nullptr && collider2->isTrigger)
//         {
//             //todo:			collider1.DoTrigger(&collider1)
//             collider2->SetTriggerEnterCallback();
//         }
//
//         if (body1->GetPosition().y < 51)
//         {
//             contact->SetEnabled(false);
//         }
//
//         std::cout << "done" << std::endl;
//     }
// };
//
// #endif //MYCONTACTLISTENER_HPP
