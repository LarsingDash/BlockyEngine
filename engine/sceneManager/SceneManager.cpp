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

	TypeProperties p(COLLIDER, true, false, {2, 0}, 100, 0, 0, true);

	auto& leftParent = testScene->AddChild("Box_Collider_Red");
	auto& rightParent = testScene->AddChild("RightParent");

	p.isStatic = true;

	leftParent.transform->Translate(4, 6);
	leftParent.transform->Rotate(10);
	leftParent.AddComponent<RectangleRenderable>("Box_Collider_Red_Rigid", glm::vec4{255, 0, 0, 255}, true);
	auto& box1 = leftParent.AddComponent<BoxRigidBody>("Box_Collider_Red_Rigid", p.isTrigger, p.isStatic, p.velocity,
	                                                   p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                                   p.gravityEnabled, w, h);
	auto& child1 = testScene->AddChild("Circle_Collider_Red");
	child1.transform->Translate(6, 6);
	child1.AddComponent<EllipseRenderable>("Circle_Collider_Red", glm::vec4{255, 0, 0, 255}, false);
	auto& circle1 = child1.AddComponent<CircleCollider>("Circle_Collider_Red", p.isTrigger, p.isStatic, r);
	auto& child2 = testScene->AddChild("Box_Collider_Red_Rigid");

	p.isStatic = false;

	child2.transform->Translate(4, 0);
	child2.transform->Rotate(10);
	child2.AddComponent<RectangleRenderable>("Box_Collider_Red_Rigid", glm::vec4{255, 0, 0, 255}, true);
	auto& boxr1 = child2.AddComponent<BoxRigidBody>("Box_Collider_Red_Rigid", p.isTrigger, p.isStatic, p.velocity,
	                                                p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                                p.gravityEnabled, w, h);
	auto& child3 = testScene->AddChild("Circle_Collider_Red_Rigid");
	child3.transform->Translate(6, 0);
	child3.AddComponent<EllipseRenderable>("Circle_Collider_Red_Rigid", glm::vec4{255, 0, 0, 255}, true);
	auto& circler1 = child3.AddComponent<CircleRigidBody>("Circle_Collider_Red_Rigid", p.isTrigger, p.isStatic,
	                                                      p.velocity,
	                                                      p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                                      p.gravityEnabled, r);

	p = TypeProperties(RIGIDBODY, true, false, {0, 0}, 10, 0.1, 0.1, false);

	rightParent.transform->Translate(4, 4);
	rightParent.AddComponent<RectangleRenderable>("Box_Collider_Green", glm::vec4{0, 255, 0, 255}, false);
	auto& box2 = rightParent.AddComponent<BoxCollider>("Box_Collider_Green", p.isTrigger, p.isStatic, w, h);
	auto& child11 = testScene->AddChild("Circle_Collider_Green");
	child11.transform->Translate(6, 4);
	child11.AddComponent<EllipseRenderable>("Circle_Collider_Green", glm::vec4{0, 255, 0, 255}, false);
	auto& circle2 = child11.AddComponent<CircleCollider>("Circle_Collider_Green", p.isTrigger, p.isStatic, r);
	auto& child12 = testScene->AddChild("Box_Collider_Green_Rigid");
	child12.transform->Translate(4, 2);
	child12.AddComponent<RectangleRenderable>("Box_Collider_Green_Rigid", glm::vec4{0, 255, 0, 255}, true);
	auto& boxr2 = child12.AddComponent<BoxRigidBody>("Box_Collider_Green_Rigid", p.isTrigger, p.isStatic, p.velocity,
	                                                 p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                                 p.gravityEnabled, w, h);
	auto& child13 = testScene->AddChild("Circle_Collider_Green_Rigid");
	child13.transform->Translate(6, 2);
	child13.AddComponent<EllipseRenderable>("Circle_Collider_Green_Rigid", glm::vec4{0, 255, 0, 255}, true);
	auto& circler2 = child13.AddComponent<CircleRigidBody>("Circle_Collider_Green_Rigid", p.isTrigger, p.isStatic,
	                                                       p.velocity,
	                                                       p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                                       p.gravityEnabled, r);

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
