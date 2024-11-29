//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"
#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"
#include "components/animation/AnimationController.hpp"
#include "components/renderables/AnimationRenderable.hpp"

SceneManager::SceneManager() :
		testScene(std::make_unique<GameObject>("root")),
		recalculationList() {
	testScene->transform->SetPosition(400, 300);
	testScene->transform->Scale(50, 50);

	auto& leftParent = testScene->AddChild("LeftParent");
	auto& rightParent = testScene->AddChild("RightParent");

	leftParent.transform->Translate(-3, 0);
	leftParent.AddComponent<RectangleRenderable>("LeftR", glm::vec4{255, 0, 0, 255}, true);

	rightParent.transform->Translate(3, 0);
	rightParent.AddComponent<RectangleRenderable>("RightR", glm::vec4{0, 255, 0, 255}, true);

	auto& child = leftParent.AddChild("Child");
	auto& childChild = child.AddChild("ChildChild");
	childChild.transform->Translate(0, -1);

	child.AddComponent<RectangleRenderable>("ChildR", glm::vec4{0, 0, 255, 255});
	childChild.AddComponent<RectangleRenderable>("ChildChildR", glm::vec4{255, 255, 255, 255});

	child.Reparent(rightParent);
	childChild.Destroy();
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