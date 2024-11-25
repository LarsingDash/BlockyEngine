//
// Created by larsv on 12/11/2024.
//

#include "SceneManager.hpp"

#include <components/collider/BoxCollider.hpp>
#include <components/collider/Collider.hpp>
#include <logging/BLogger.hpp>

#include "components/collider/CircleCollider.hpp"
#include "components/renderables/Renderable.hpp"
#include "components/renderables/RectangleRenderable.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/renderables/SpriteRenderable.hpp"

SceneManager::SceneManager() : testScene{}
{
	testScene.reserve(10);

	float x, y;
	float w, h, r;
	auto& objectA = testScene.emplace_back(std::make_unique<GameObject>("objectA"));
	auto& objectB = testScene.emplace_back(std::make_unique<GameObject>("objectB"));
	x = 0.f, y = 200.f;
	w = 200.f, h = 200.f;

	//aA with default pos (50, 50)
	auto& aA = objectA->AddComponent<RectangleRenderable>("aA", glm::ivec4(255, 0, 0, 255), true);
	auto& aB = objectA->AddComponent<BoxCollider>("BoxColliderA", true, false, w, h);
	objectA->transform->position = glm::vec2(x, y);
	aA.componentTransform->position = {x, y};
	aB.componentTransform->position = {x, y};
	BLOCKY_ENGINE_DEBUG(objectA->transform->position)

	x = 0.f, y = 200.f;
	r = 50.f;
	auto& bA = objectB->AddComponent<RectangleRenderable>("bA", glm::ivec4(0, 255, 0, 255));
	auto& bB = objectB->AddComponent<CircleCollider>("CircleColliderB", true, false, r);
	objectB->transform->position = glm::vec2(x, y);
	bA.componentTransform->position = {x, y};
	bB.componentTransform->position = {x, y};
	BLOCKY_ENGINE_DEBUG(objectA->transform->position)

	// x = -10.f, y = -10.f, r = 500.f;
	// auto& ellipseA = objectA->AddComponent<EllipseRenderable>("ellipseA", glm::ivec4(0, 255, 0, 255));
	// ellipseA.componentTransform->position = glm::vec2{x, y};
	// ellipseA.componentTransform->scale = glm::vec2{w, h};
	// ellipseA.gameObject.AddComponent<CircleCollider>("CircleColliderA", true, r);
	//
	// auto& ellipseB = objectB->AddComponent<EllipseRenderable>("ellipseB", glm::ivec4(0, 0, 255, 255), true);
	// ellipseB.componentTransform->position = glm::vec2{200.f, 150.f};
	// ellipseB.componentTransform->scale = glm::vec2{150.f, 100.f};
	//
	// auto& spriteA = objectB->AddComponent<SpriteRenderable>("spriteA", "../assets/kaboom.png", "kaboom");
	// spriteA.componentTransform->position = glm::vec2{350.f, 150.f};
	// spriteA.componentTransform->rotation = -65.f;
}

void SceneManager::Update(float delta)
{
	for (auto& gameObject : testScene)
	{
		gameObject->Update(delta);
	}
}
