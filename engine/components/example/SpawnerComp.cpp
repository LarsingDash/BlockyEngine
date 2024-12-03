//
// Created by larsv on 29/11/2024.
//

#include "SpawnerComp.hpp"

#include "gameObject/GameObject.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/example/MovementComp.hpp"

#include <memory>

SpawnerComp::SpawnerComp(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false), projectilePrefab(nullptr) {
	projectilePrefab = std::make_unique<GameObject>("ProjectilePrefab");
	projectilePrefab->AddComponent<EllipseRenderable>("ProjSprite", glm::vec4{255, 255, 0, 255}, true);
	projectilePrefab->AddComponent<MovementComp>("Movement");
}

SpawnerComp::~SpawnerComp() = default;

SpawnerComp::SpawnerComp(const SpawnerComp& other) :
		Component(other), projectilePrefab(std::make_unique<GameObject>(*other.projectilePrefab)) {}

Component* SpawnerComp::_cloneImpl(GameObject& parent) {
	auto clone = new SpawnerComp(*this);
	clone->projectilePrefab->SetParent(parent);
	return clone;
}

void SpawnerComp::Start() {}

constexpr float interval = 0.5f;
void SpawnerComp::Update(float delta) {
	counter += delta;
	if (counter >= interval) {
		counter -= interval;
		gameObject->AddChild(*projectilePrefab);
	}
}

void SpawnerComp::End() {}
