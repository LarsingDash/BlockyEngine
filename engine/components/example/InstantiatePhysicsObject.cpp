//
// Created by doguk on 12/17/2024.
//

#include "InstantiatePhysicsObject.h"

#include <components/physics/rigidBody/BoxRigidBody.hpp>

#include "components/physics/collider/BoxCollider.hpp"
#include "components/renderables/RectangleRenderable.hpp"

#include "gameObject/GameObject.hpp"

InstantiatePhysicsObject::InstantiatePhysicsObject(GameObject* gameObject, const char* tag): Component(gameObject, tag),
    container(nullptr) {
    physicsGO = std::make_unique<GameObject>("PhysicsObject");
    physicsGO->SetActive(false);

    //Creation time
    physicsGO->AddComponent<RectangleRenderable>("PhysicsObjMesh", glm::vec4{255, 255, 0, 255}, 1, true);

    //Physics
    TypeProperties properties(
        RIGIDBODY,
        false,
        glm::vec2{0, 1},
        0,
        0,
        0,
        true
    );
    physicsGO->AddComponent<BoxRigidBody>("BoxColl", properties);
}

InstantiatePhysicsObject::~InstantiatePhysicsObject() = default;

InstantiatePhysicsObject::InstantiatePhysicsObject(const InstantiatePhysicsObject& other): Component(other),
    physicsGO(std::make_unique<GameObject>(*other.physicsGO)), container(other.container) {}

void InstantiatePhysicsObject::Start() {}

void InstantiatePhysicsObject::Update(float delta) {}

void InstantiatePhysicsObject::End() {}

Component* InstantiatePhysicsObject::_clone(const GameObject& parent) {
    auto clone = new InstantiatePhysicsObject(*this);
    return clone;
}
