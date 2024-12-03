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
#include "components/physics/collision/CollisionHandler.hpp"
#include "components/renderables/AnimationRenderable.hpp"

float x = 400, y = 100;
float w = 50, h = 50, r = 25;

SceneManager::SceneManager() :
	testScene(std::make_unique<GameObject>("root")),
	recalculationList() {
	testScene->transform->SetPosition(x, y);
	testScene->transform->Scale(w, h);

	TypeProperties p(COLLIDER, false, {2, 0}, 100, 0, 0, true);

	auto& leftParent = testScene->AddChild("Box_Collider_Red");
	auto& rightParent = testScene->AddChild("RightParent");

	p.isStatic = false;
	auto rigid = glm::vec4{255, 0, 0, 255};
	auto box = glm::vec4{0, 0, 0, 0};
	auto collider = glm::vec4{0, 255, 0, 255};
	auto circle = glm::vec4{0, 0, 0, 0};

	leftParent.transform->Translate(0, 6);
	leftParent.transform->Rotate(10);
	leftParent.AddComponent<RectangleRenderable>("", rigid + box, p.isStatic);
	leftParent.AddComponent<BoxRigidBody>("", p.isStatic, p.velocity,
	                                      p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                      p.gravityEnabled, w, h);
	leftParent.AddComponent<EllipseRenderable>("", collider + circle, p.isStatic);
	leftParent.AddComponent<CircleCollider>("", r);
	leftParent.AddComponent<CollisionHandler>("", [](GameObject* obj1, GameObject* obj2) {
		std::cout << "CollisionHandler1: " << obj1->tag << ", " << obj2->tag << std::endl;
	});

	auto& child1 = testScene->AddChild("");
	child1.transform->Translate(2, 6);
	child1.AddComponent<EllipseRenderable>("", collider + circle, p.isStatic);
	child1.AddComponent<CircleCollider>("", r);
	p.isStatic = false;
	auto& child2 = testScene->AddChild("");
	child2.transform->Translate(0, 0);
	child2.transform->Rotate(10);
	child2.AddComponent<RectangleRenderable>("", rigid + box, p.isStatic);
	child2.AddComponent<BoxRigidBody>("", p.isStatic, p.velocity,
	                                  p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                  p.gravityEnabled, w, h);
	child2.AddComponent<CollisionHandler>("", [](GameObject* obj1, GameObject* obj2) {
		std::cout << "CollisionHandler2: " << obj1->tag << ", " << obj2->tag << std::endl;
	});

	auto& child3 = testScene->AddChild("");
	child3.transform->Translate(2, 0);
	child3.AddComponent<EllipseRenderable>("", rigid + circle, p.isStatic);
	child3.AddComponent<CircleRigidBody>("", p.isStatic,
	                                     p.velocity,
	                                     p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                     p.gravityEnabled, r);
	p = TypeProperties(RIGIDBODY, false, {0, 0}, 10, 0.1, 0.1, false);
	rightParent.transform->Translate(0, 4);
	rightParent.AddComponent<RectangleRenderable>("", collider + box, p.isStatic);
	rightParent.AddComponent<BoxCollider>("", w, h);
	rightParent.AddComponent<EllipseRenderable>("", collider + circle, p.isStatic);
	rightParent.AddComponent<CircleCollider>("", r);
	auto& child11 = testScene->AddChild("");
	child11.transform->Translate(2, 4);
	child11.AddComponent<EllipseRenderable>("", rigid + circle, p.isStatic);
	child11.AddComponent<CircleRigidBody>("", p.isStatic,
	                                      p.velocity,
	                                      p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                      p.gravityEnabled, r);
	child11.AddComponent<RectangleRenderable>("", rigid + box, p.isStatic);
	child11.AddComponent<BoxRigidBody>("", p.isStatic,
	                                   p.velocity,
	                                   p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                   p.gravityEnabled, w, h);
	auto& child12 = testScene->AddChild("");
	child12.transform->Translate(0, 2);
	child12.AddComponent<RectangleRenderable>("", rigid + box, p.isStatic);
	child12.AddComponent<BoxRigidBody>("", p.isStatic, p.velocity,
	                                   p.rotationVelocity, p.angularResistance, p.linearResistance,
	                                   p.gravityEnabled, w, h);

	auto& child13 = testScene->AddChild("");
	child13.transform->Translate(2, 2);
	child13.AddComponent<EllipseRenderable>("", rigid + circle, p.isStatic);
	child13.AddComponent<CircleRigidBody>("", p.isStatic,
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
