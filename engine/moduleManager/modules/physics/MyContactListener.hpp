//
// Created by hmkam on 22/11/2024.
//
#ifndef MYCONTACTLISTENER_HPP
#define MYCONTACTLISTENER_HPP
#include <unordered_map>
#include <box2d/b2_contact.h>
#include <box2d/b2_world_callbacks.h>
#include "components/physics/PhysicsBody.hpp"

class MyContactListener : public b2ContactListener {
public:
    std::unordered_map<GameObject*, b2Body*>* _gameObjectToBodyMap;
    explicit MyContactListener(std::unordered_map<GameObject*, b2Body*>* gameObjectToBodyMap);
    ~MyContactListener() override = default;
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
};
#endif //MYCONTACTLISTENER_HPP
