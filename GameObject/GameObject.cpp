//
// Created by larsv on 23/09/2024.
//

#include "GameObject.h"

GameObject::GameObject(std::string t, Transform* parent)
		: tag(std::move(t)), transform(new Transform(this, parent)) {}

void GameObject::OnUpdate(float delta) {  // NOLINT(*-no-recursion)
	//Cascade update to components
	for (auto& types: components) {
		for (auto& component: types.second) {
			component->OnUpdate(delta);
		}
	}

	//Cascade update to child objects
	for (auto& child: transform->getChildren()) {
		child->gameObject->OnUpdate(delta);
	}
}

GameObject::~GameObject() {
	//Delete transform (which will delete child objects)
	delete transform;

	//Delete all components
	for (auto& types: components) {
		for (auto& component: types.second) {
			delete component;
		}
	}
}
