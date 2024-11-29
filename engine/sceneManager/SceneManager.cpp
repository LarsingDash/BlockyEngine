//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <components/physics/collider/BoxCollider.hpp>
#include <components/physics/collider/CircleCollider.hpp>
#include <components/physics/rigidBody/BoxRigidBody.hpp>
#include <components/physics/rigidBody/CircleRigidBody.hpp>

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

    auto& leftParent = testScene->AddChild("BoxColliderL");
    auto& rightParent = testScene->AddChild("RightParent");

    leftParent.transform->Translate(-0.3, 0);
    leftParent.AddComponent<RectangleRenderable>("BoxColliderL", glm::vec4{255, 0, 0, 255}, false);
    auto& box1 = leftParent.AddComponent<BoxCollider>("BoxColliderL", false, false, w, h);
    auto& child1 = testScene->AddChild("CircleColliderL");
    child1.transform->Translate(-0.6, 0);
    child1.AddComponent<EllipseRenderable>("CircleColliderL", glm::vec4{255, 0, 0, 255}, false);
    auto& circle1 = child1.AddComponent<CircleCollider>("CircleColliderL", false, false, r);
    auto& child2 = testScene->AddChild("BoxColliderL");
    child2.transform->Translate(-0.9, 0);
    child2.AddComponent<RectangleRenderable>("BoxColliderL", glm::vec4{255, 0, 0, 255}, true);
    auto& boxr1 = child2.AddComponent<BoxRigidBody>("BoxColliderL", false, false, w, h);
    auto& child3 = testScene->AddChild("CircleRigidBody");
    child3.transform->Translate(-1.3, 0);
    child3.AddComponent<EllipseRenderable>("CircleRigidBody", glm::vec4{255, 0, 0, 255}, true);
    auto& circler1 = child3.AddComponent<CircleRigidBody>("CircleRigidBody", false, false, r);

    rightParent.transform->Translate(0.3, 0);
    rightParent.AddComponent<RectangleRenderable>("BoxColliderR", glm::vec4{0, 255, 0, 255}, false);
    auto& box2 = rightParent.AddComponent<BoxCollider>("BoxColliderR", true, false, w, h);
    auto& child11 = testScene->AddChild("CircleColliderR");
    child11.transform->Translate(-0.6, 0);
    child11.AddComponent<EllipseRenderable>("CircleColliderR", glm::vec4{0, 255, 0, 255}, false);
    auto& circle2 = child11.AddComponent<CircleCollider>("CircleColliderR", true, false, r);
    auto& child12 = testScene->AddChild("BoxColliderR");
    child12.transform->Translate(-0.9, 0);
    child12.AddComponent<RectangleRenderable>("BoxColliderR", glm::vec4{0, 255, 0, 255}, true);
    auto& boxr2 = child1.AddComponent<BoxRigidBody>("BoxColliderR", true, false, w, h);
    auto& child13 = testScene->AddChild("CircleColliderR");
    child13.transform->Translate(-1.3, 0);
    child13.AddComponent<EllipseRenderable>("CircleColliderR", glm::vec4{0, 255, 0, 255}, true);
    auto& circler2 = child2.AddComponent<CircleRigidBody>("CircleColliderR", true, false, r);

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
