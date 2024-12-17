//
// Created by hmkam on 03/12/2024.
//

#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include <functional>
#include <components/Component.hpp>
#include <components/physics/PhysicsBody.hpp>

class CollisionHandler : public Component {
public:
    CollisionHandler(GameObject *gameObject, const char *tag, const PhysicsBody& body,
                     std::function<void(GameObject &)> onEntryCallback,
                     std::function<void(GameObject &)> onExitCallback);

    ~CollisionHandler() override = default;

    // virtual void HandleCollision(GameObject* obj1, GameObject* obj2);

    void Start() override;

    void Update(float delta) override {
    };

    void End() override;

private:
    std::function<void(GameObject &)> _onEntryHandler;
    std::function<void(GameObject &)> _onExitHandler;

    PhysicsBody _body;

    Component *_clone(const GameObject &parent) override;

    friend class MyContactListener;
};

#endif //COLLISIONHANDLER_HPP
