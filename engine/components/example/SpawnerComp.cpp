//
// Created by larsv on 29/11/2024.
//

#include "SpawnerComp.hpp"

#include "gameObject/GameObject.hpp"
#include "components/renderables/EllipseRenderable.hpp"
#include "components/example/MovementComp.hpp"

#include <memory>

SpawnerComp::SpawnerComp(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag), projectilePrefab(nullptr), container(nullptr) {
	projectilePrefab = std::make_unique<GameObject>("ProjectilePrefab");
	projectilePrefab->SetActive(false);
	projectilePrefab->AddComponent<EllipseRenderable>("ProjEl", glm::vec4{255, 255, 0, 255}, true);
	projectilePrefab->AddComponent<MovementComp>("Movement");
	projectilePrefab->AddChild("Dot")
			.AddComponent<EllipseRenderable>("DotEl", glm::vec4{150, 0, 0, 255}, true)
			.gameObject->transform->SetScale(.75f, .75f);
}

SpawnerComp::~SpawnerComp() = default;

SpawnerComp::SpawnerComp(const SpawnerComp& other) :
		Component(other), container(nullptr),
		projectilePrefab(std::make_unique<GameObject>(*other.projectilePrefab)) {}

Component* SpawnerComp::_clone(const GameObject& parent) {
	auto clone = new SpawnerComp(*this);
	return clone;
}

void SpawnerComp::Start() {
	container = gameObject->parent->GetChild("ProjectileContainer");
	if (container) projectilePrefab->SetParent(*container);
}

constexpr float interval = 0.33f;
void SpawnerComp::Update(float delta) {
	counter += delta;
	if (counter >= interval) {
		counter -= interval;
		if (container) {
			auto& projectile = container->AddChild(*projectilePrefab);
			projectile.GetComponent<MovementComp>()->SetDirectionByAngle(gameObject->transform->GetWorldRotation());
		}
	}
}

void SpawnerComp::End() {}
