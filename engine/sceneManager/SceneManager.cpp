//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <iostream>

#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"

SceneManager::SceneManager() : testScene{} {
	testScene.reserve(2);

	auto& objectA = testScene.emplace_back(std::make_unique<GameObject>("objectA"));
	auto& objectB = testScene.emplace_back(std::make_unique<GameObject>("objectB"));

	//aA with default pos (50, 50)
    objectA->AddComponent<RectangleRenderable>("aA", glm::ivec4(255, 0, 0, 255));
	
	//bA with (50, 150)
    auto& bA = objectB->AddComponent<RectangleRenderable>("bA", glm::ivec4(0, 255, 0, 255));
    bA.componentTransform->position = glm::vec2{50.f, 200.f};
}

void SceneManager::Update(float delta) {
	for (auto& gameObject: testScene) {
		gameObject->Update(delta);
	}
}