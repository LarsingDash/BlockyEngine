//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <iostream>

#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

SceneManager::SceneManager() : testScene{} {
	testScene.reserve(10);

	auto& objectA = testScene.emplace_back(std::make_unique<GameObject>("objectA"));
	auto& objectB = testScene.emplace_back(std::make_unique<GameObject>("objectB"));

	//aA with default pos (50, 50)
    objectA->AddComponent<RectangleRenderable>("aA", glm::ivec4(255, 0, 0, 255));
	
	//bA with (50, 150)
    auto& bA = objectB->AddComponent<RectangleRenderable>("bA", glm::ivec4(0, 255, 0, 255));
    bA.componentTransform->position = glm::vec2{50.f, 150.f};

    auto& ellipseA = objectA->AddComponent<EllipseRenderable>("ellipseA", glm::ivec4(0, 255, 0, 255));
    ellipseA.componentTransform->position = glm::vec2{150.f, 50.f};

    auto& ellipseB = objectB->AddComponent<EllipseRenderable>("ellipseB", glm::ivec4(0, 0, 255, 255));
    ellipseB.componentTransform->position = glm::vec2{170.f, 170.f};
    ellipseB.componentTransform->scale = glm::vec2{150.f, 100.f};

    auto& spriteA = objectB->AddComponent<SpriteRenderable>("spriteA", "E:\\C++\\Blocky Engine Minor\\BlockyEngine\\assets\\triangle.png", "triangleSprite");
    spriteA.componentTransform->position = glm::vec2{200.f, 200.f};
    spriteA.componentTransform->rotation = 45.f;


}

void SceneManager::Update(float delta) {
	for (auto& gameObject: testScene) {
		gameObject->Update(delta);
	}
}