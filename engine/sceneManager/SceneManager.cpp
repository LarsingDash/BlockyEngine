//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <iostream>

SceneManager::SceneManager() : testScene{} {
	testScene.reserve(3);
	//Create:
	//A
	//	Untagged Component
	//	Changed Tag
	//B
	//	1
	//	2
	//	3
	//C
	auto& objectA = testScene.emplace_back(std::make_unique<GameObject>("objectA"));
	objectA->AddComponent<Component>();
	auto& changedA = objectA->AddComponent<Component>("temp");
	changedA.tag = "ChangedA";

	auto& objectB = testScene.emplace_back(std::make_unique<GameObject>("objectB"));
	objectB->AddComponent<Component>("B1");
	objectB->AddComponent<Component>("B2");
	objectB->AddComponent<Component>("B3");
	objectB->AddComponent<Component>("B4");

	auto& objectC = testScene.emplace_back(std::make_unique<GameObject>("objectC"));
	objectC->AddComponent<Component>("TEMP");

	//Remove B2 and first in objectB
	objectB->RemoveComponent<Component>("B2");
	objectB->RemoveComponent<Component>();

	//Get first (B3) and rename it to ChangedB1
	auto* changedB1 = objectB->GetComponent<Component>();
	changedB1->tag = "ChangedB1";

	//Get B4 and rename it to ChangedB2
	auto* changedB2 = objectB->GetComponent<Component>("B4");
	changedB2->tag = "ChangedB2";

	//Get B4, which should now return nullptr since it's been renamed
	auto* b4 = objectB->GetComponent<Component>("B4");
	if (b4 != nullptr) throw std::runtime_error("B4 should be nullptr");

	//Remove objectC's TEMP, which should, removing again shouldn't do anything
	objectC->RemoveComponent<Component>("TEMP");
	objectC->RemoveComponent<Component>();

	//Nothing should be found now in objectC
	auto* TEMP = objectC->GetComponent<Component>();
	if (TEMP != nullptr) throw std::runtime_error("TEMP should be nullptr");
}

void SceneManager::Update(float delta) {
	for (auto& gameObject: testScene) {
		gameObject->Update(delta);
	}
	std::cout << "-----" << std::endl;
}
