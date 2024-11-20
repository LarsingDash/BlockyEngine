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

SceneManager::SceneManager() : testScene{} {
	testScene.reserve(10);

	auto& objectA = testScene.emplace_back(std::make_unique<GameObject>("objectA"));
	auto& objectB = testScene.emplace_back(std::make_unique<GameObject>("objectB"));
	auto& objectC = testScene.emplace_back(std::make_unique<GameObject>("objectC"));

	//aA with default pos (50, 50)
	auto& aA = objectA->AddComponent<RectangleRenderable>("aA", glm::ivec4(255, 0, 0, 255), true);
	aA.componentTransform->rotation = 36.f;

	//bA with (50, 150)
	auto& bA = objectB->AddComponent<RectangleRenderable>("bA", glm::ivec4(0, 255, 0, 255));
	bA.componentTransform->position = glm::vec2{50.f, 150.f};

	auto& ellipseA = objectA->AddComponent<EllipseRenderable>("ellipseA", glm::ivec4(0, 255, 0, 255));
	ellipseA.componentTransform->position = glm::vec2{150.f, 50.f};

	auto& ellipseB = objectB->AddComponent<EllipseRenderable>("ellipseB", glm::ivec4(0, 0, 255, 255), true);
	ellipseB.componentTransform->position = glm::vec2{200.f, 150.f};
	ellipseB.componentTransform->scale = glm::vec2{150.f, 100.f};

	auto& spriteA = objectB->AddComponent<SpriteRenderable>("spriteA", "../assets/kaboom.png", "kaboom");
	spriteA.componentTransform->position = glm::vec2{350.f, 150.f};
	spriteA.componentTransform->scale = glm::vec2{200.f, 200.f};

	auto& animatedObject = objectC->AddComponent<AnimationRenderable>("animTag", "../assets/character_spritesheet.png",
																	  "spriteTag", 32, 32);

	animatedObject.componentTransform->scale = glm::vec2{200.f, 200.f};
	animatedObject.componentTransform->position = glm::vec2{100.f, 100.f};

	auto& animationController = objectC->AddComponent<AnimationController>("animControllerTag", animatedObject);
	animationController.SetFrameDuration(0.15f);

	animationController.AddAnimation("idle", 0, 7, true);
	animationController.AddAnimation("run", 8, 15, true);

	animationController.PlayAnimation("idle");
}

void SceneManager::Update(float delta) {
	for (auto& gameObject : testScene) {
		gameObject->Update(delta);
	}

}