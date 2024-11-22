//
// Created by hmkam on 22/11/2024.
//

#ifndef MYCONTACTLISTENER_HPP
#define MYCONTACTLISTENER_HPP
#include <unordered_map>
#include <box2d/b2_contact.h>
#include <box2d/b2_world_callbacks.h>
#include <components/collider/Collider.hpp>
#include <logging/BLogger.hpp>
#include <utility>

//todo: move
class MyContactListener : public b2ContactListener
{
public:
    std::unordered_map<Collider*, b2Body*>* _colliderToBodyMap;

    explicit MyContactListener(std::unordered_map<Collider*, b2Body*>* colliderToBodyMap);
    ~MyContactListener() override = default;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
};

#endif //MYCONTACTLISTENER_HPP
