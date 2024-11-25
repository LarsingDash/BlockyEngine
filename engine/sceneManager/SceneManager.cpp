//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <iostream>
#include <components/collider/BoxCollider.hpp>
#include <components/collider/CircleCollider.hpp>
#include <logging/BLogger.hpp>

#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

SceneManager::SceneManager() : testScene(std::make_unique<GameObject>("root"))
{
	float x, y;
	float w, h, r;
	auto& objectA = testScene->AddChild("objectA");
	auto& objectB = testScene->AddChild("objectB");
	x = 0.f, y = 200.f;
	w = 200.f, h = 200.f;

	auto& aRed = objectA.AddComponent<RectangleRenderable>("Red", glm::vec4{255, 0, 0, 255}, true);
	auto& aBoxCollider = objectA.AddComponent<BoxCollider>("BoxColliderA", true, false, w, h);
	objectA.transform->position = glm::vec2(x, y);
	aRed.componentTransform->position = glm::vec2{x, y};
	aBoxCollider.componentTransform->position = glm::vec2{x, y};
	BLOCKY_ENGINE_DEBUG(objectA.transform->position)

	x = 0.f, y = 200.f;
	r = 50.f;
	auto& bA = objectB.AddComponent<EllipseRenderable>("bA", glm::ivec4(0, 255, 0, 255));
	auto& bB = objectB.AddComponent<CircleCollider>("CircleColliderB", true, false, r);
	objectB.transform->position = glm::vec2(x, y);
	bA.componentTransform->position = glm::vec2{x, y};
	bB.componentTransform->position = glm::vec2{x, y};
	BLOCKY_ENGINE_DEBUG(objectA.transform->position)

	std::cout << testScene->RemoveChild(*testScene->GetChild("A")) << std::endl;
}

void SceneManager::Update(float delta) { testScene->Update(delta); }



