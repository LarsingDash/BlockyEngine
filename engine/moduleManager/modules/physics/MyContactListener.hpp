//
// Created by hmkam on 22/11/2024.
//
#ifndef MYCONTACTLISTENER_HPP
#define MYCONTACTLISTENER_HPP
#include <unordered_map>
#include <box2d/b2_contact.h>
#include <box2d/b2_world_callbacks.h>
#include "components/physics/PhysicsBody.hpp"

struct Body;

class MyContactListener : public b2ContactListener {
public:
    explicit MyContactListener(std::unordered_map<PhysicsBody*, Body*>* gameObjectToBodyMap);
    ~MyContactListener() override = default;

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

private:
    std::unordered_map<PhysicsBody*, Body*>* _physicsBodyToBodyMap;
    std::pair<GameObject*, GameObject*> _gameObjects(b2Contact* contact) const;
};
#endif //MYCONTACTLISTENER_HPP
