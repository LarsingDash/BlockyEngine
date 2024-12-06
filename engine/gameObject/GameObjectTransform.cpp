//
// Created by larsv on 22/11/2024.
//

#include "gameObject/GameObject.hpp"

#include "GameObjectTransform.hpp"

GameObjectTransform::GameObjectTransform(GameObject& gameObject) : Transform(gameObject) {
	if (gameObject.parent) _parent = gameObject.parent->transform.get();
	_recalculateWorldMatrix();
}

void GameObjectTransform::RecalculateWorldMatrix() {
	// NOLINT(*-no-recursion)
	//Update self
	_recalculateWorldMatrix();

	//Update components
	for (const auto& [key, list] : gameObject.GetComponents()) {
		for (const auto& component : list) {
			if (component->componentTransform) component->componentTransform->RecalculateWorldMatrix();
		}
	}

	//Update children
	for (const auto& child : gameObject.GetChildren()) {
		child->transform->RecalculateWorldMatrix();
	}
}
