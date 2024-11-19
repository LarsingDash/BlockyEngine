//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"
#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

SceneManager::SceneManager() : testScene{std::make_unique<GameObject>("root")} {
	auto& a = testScene->children.emplace_back(std::make_unique<GameObject>("A", testScene.get()));
	auto& sprite = a->AddComponent<SpriteRenderable>("Kaboom", "../assets/kaboom.png", "Kaboom");
	sprite.componentTransform->position = glm::vec2{100, 50};
	sprite.componentTransform->scale = glm::vec2{200, 100};

	auto& b = testScene->children.emplace_back(std::make_unique<GameObject>("B", testScene.get()));
	auto& bRed = b->AddComponent<RectangleRenderable>("Red", glm::vec4{255, 0, 0, 255}, true);
	bRed.componentTransform->position = glm::vec2{50, 150};
	auto& bBlue = b->AddComponent<EllipseRenderable>("Blue", glm::vec4{0, 0, 255, 255}, true);
	bBlue.componentTransform->position = glm::vec2{150, 150};
}

void SceneManager::Update(float delta) { testScene->Update(delta); }