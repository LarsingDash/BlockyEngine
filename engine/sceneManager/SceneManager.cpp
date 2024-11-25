//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

SceneManager::SceneManager() :
		testScene(std::make_unique<GameObject>("root")),
		recalculationList() {
	recalculationList.reserve(25);

	testScene->transform->SetPosition(250, 250);
	auto& row = testScene->AddChild("TopRow");
	row.transform->SetRotation(10);
	row.transform->SetScale(200, 50);
	row.AddComponent<SpriteRenderable>("Kaboom", "../assets/kaboom.png", "Kaboom");

	auto& tRLeft = row.AddChild("tRLeft");
	tRLeft.AddComponent<EllipseRenderable>("tRLeftR", glm::vec4{255, 0, 0, 255}, true);
	tRLeft.transform->SetRotation(-35);
	tRLeft.transform->SetScale(0.25f, 1);
	tRLeft.transform->Translate(-0.5f + tRLeft.transform->GetLocalScale().x / 2.f, 0);

	auto& tRRight = row.AddChild("trRight");
	tRRight.AddComponent<RectangleRenderable>("trRightR", glm::vec4{0, 255, 0, 255}, true);
	tRRight.transform->SetRotation(25);
	tRRight.transform->SetScale(0.5f, 1);
	tRRight.transform->Translate(0.5f - tRRight.transform->GetLocalScale().x / 2.f, 0);

	auto& test = tRRight.AddChild("Test");
	test.transform->SetRotation(15);
	test.AddComponent<RectangleRenderable>("TestR", glm::vec4{0, 0, 255, 255});
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