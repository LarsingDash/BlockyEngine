//
// Created by doguk on 12/17/2024.
//

#ifndef INSTANTIATEPHYSICSOBJECT_H
#define INSTANTIATEPHYSICSOBJECT_H
#include "components/Component.hpp"


class InstantiatePhysicsObject : public Component {
public:
    InstantiatePhysicsObject(GameObject* gameObject, const char* tag);
    ~InstantiatePhysicsObject() override;

    InstantiatePhysicsObject(const InstantiatePhysicsObject& physicsSpawner);

    void Start() override;

    void Update(float delta) override;

    void End() override;

private:

    GameObject* container;
    std::unique_ptr<GameObject> physicsGO;

    Component* _clone(const GameObject &parent) override;
};



#endif //INSTANTIATEPHYSICSOBJECT_H