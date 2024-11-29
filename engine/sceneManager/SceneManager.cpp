//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <components/physics/collider/BoxCollider.hpp>
#include <components/physics/collider/CircleCollider.hpp>
#include <components/physics/rigidBody/BoxRigidBody.hpp>
#include <components/physics/rigidBody/CircleRigidBody.hpp>
#include <components/physics/shape/Circle.hpp>

#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "components/animation/AnimationController.hpp"
#include "components/renderables/AnimationRenderable.hpp"

float x = 400, y = 100;
float w = 50, h = 50, r = 25;

SceneManager::SceneManager() :
    testScene(std::make_unique<GameObject>("root")),
    recalculationList() {
    testScene->transform->SetPosition(x, y);
    testScene->transform->Scale(w, h);

    auto& leftParent = testScene->AddChild("LeftParent");
    auto& rightParent = testScene->AddChild("RightParent");

    // leftParent.transform->Translate(-3, 0);
    leftParent.AddComponent<RectangleRenderable>("LeftR", glm::vec4{255, 0, 0, 255}, true);
    // auto& box1 = leftParent.AddComponent<BoxCollider>("BoxColliderL", false, false, w, h);
    auto& circle1 = leftParent.AddComponent<CircleCollider>("CircleColliderL", false, false, r);
    // auto& boxr1 = leftParent.AddComponent<BoxRigidBody>("BoxColliderL", false, false, w, h);
    // auto& circler1 = leftParent.AddComponent<CircleRigidBody>("CircleRigidBody", false, false, r);

    rightParent.transform->Translate(0.5, 0);
    rightParent.AddComponent<RectangleRenderable>("RightR", glm::vec4{0, 255, 0, 255}, true);
    // auto& box2 = rightParent.AddComponent<BoxCollider>("BoxColliderR", true, false, w, h);
    auto& circle2 = rightParent.AddComponent<CircleCollider>("CircleColliderR", true, false, r);
    // auto& boxr2 = rightParent.AddComponent<BoxRigidBody>("BoxColliderR", true, false, w, h);
    // auto& circler2 = rightParent.AddComponent<CircleRigidBody>("CircleColliderR", true, false, r);

    // auto& child = leftParent.AddChild("Child");
    // auto& childChild = child.AddChild("ChildChild");
    // childChild.transform->Translate(0, -1);
    //
    // child.AddComponent<RectangleRenderable>("ChildR", glm::vec4{0, 0, 255, 255});
    // childChild.AddComponent<RectangleRenderable>("ChildChildR", glm::vec4{255, 255, 255, 255});
    //
    // child.Reparent(rightParent);
    // childChild.Destroy();
}

void SceneManager::Update(float delta) {
    //Update active scene starting from the root
    testScene->Update(delta, recalculationList);

    //Go through all transforms that marked themselves to be recalculated
    for (auto& trans : recalculationList) {
        auto& cur = trans.get();
        if (cur.isMarkedForRecalculation) cur.RecalculateWorldMatrix();
    }
    recalculationList.clear();
}
