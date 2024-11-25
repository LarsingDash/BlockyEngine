//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <iostream>

#include "components/MovementComponent.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

SceneManager::SceneManager() :
		testScene(std::make_unique<GameObject>("root")),
		recalculationList() {
	recalculationList.reserve(25);
//	testScene->transform->SetPosition(300, 300);
//	testScene->transform->SetScale(0.5, 0.5);
//	testScene->transform->SetScale(200, 50);
//	testScene->transform->SetRotation(45);
//	testScene->AddComponent<SpriteRenderable>("Kaboom", "../assets/kaboom.png", "Kaboom");
//	testScene->AddComponent<MovementComponent>();

//2222222222222222222
//	testScene->transform->SetPosition(250, 250);
//	auto& row = testScene->AddChild("TopRow");
//	row.transform->SetScale(200, 50);
////	row.AddComponent<RectangleRenderable>("TopRowBack", glm::vec4{100}, true);
//	row.AddComponent<SpriteRenderable>("Kaboom", "../assets/kaboom.png", "Kaboom");
//	row.AddComponent<MovementComponent>();
//
//	auto& tRLeft = row.AddChild("tRLeft");
//	tRLeft.AddComponent<RectangleRenderable>("tRLeftR", glm::vec4{255, 0, 0, 255}, true);
//	tRLeft.transform->SetScale(0.25f, 1);
//	tRLeft.transform->Translate(-0.5f + tRLeft.transform->GetLocalScale().x / 2.f, 0);
//	tRLeft.AddComponent<MovementComponent>();
//
//	auto& tRRight = row.AddChild("trRight");
//	tRRight.AddComponent<RectangleRenderable>("trRightR", glm::vec4{0, 255, 0, 255}, true);
//	tRRight.transform->SetScale(0.25f, 1);
//	tRRight.transform->Translate(0.5f - tRRight.transform->GetLocalScale().x / 2.f, 0);
//	tRRight.AddComponent<MovementComponent>();
//
//	auto& test = tRRight.AddChild("Test");
//	test.AddComponent<RectangleRenderable>("TestR", glm::vec4{0, 0, 255, 255});
//	test.AddComponent<MovementComponent>();

//33333333333333333
//	testScene->transform->SetPosition(300, 300);
//	testScene->transform->SetScale(50, 50);
//
//	auto& grey = testScene->AddChild("Grey");
//	grey.AddComponent<RectangleRenderable>("GreyR", glm::vec4{150}, true);
//	grey.AddComponent<MovementComponent>();
//	grey.transform->SetScale(2,1);
//	
//	auto& blue = grey.AddChild("Blue");
//	blue.AddComponent<RectangleRenderable>("BlueR", glm::vec4{0, 0, 255, 255});
//	blue.AddComponent<MovementComponent>();
//	blue.transform->SetPosition(1,0);
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