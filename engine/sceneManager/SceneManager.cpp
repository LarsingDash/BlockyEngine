//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <iostream>

#include "components/renderables/Renderable.hpp"

SceneManager::SceneManager() : testScene{} {
	testScene.reserve(2);

	auto& objectA = testScene.emplace_back(std::make_unique<GameObject>("objectA"));
	auto& objectB = testScene.emplace_back(std::make_unique<GameObject>("objectB"));

	//aA with default pos (50, 50)
	objectA->AddComponent<Renderable>("aA");
	
	//bA with (50, 150)
	auto& bA = objectB->AddComponent<Renderable>("bA");
	bA.componentTransform->position = glm::vec2{50.f, 150.f};
	
	//bB with (100, 150) pos and double width
	auto& bB = objectB->AddComponent<Renderable>("bB");
	bB.componentTransform->position = glm::vec2{100.f, 150.f};
	bB.componentTransform->scale *= glm::vec2{2.f, 1.f};
}

void SceneManager::Update(float delta) {
	for (auto& gameObject: testScene) {
		gameObject->Update(delta);
	}
}