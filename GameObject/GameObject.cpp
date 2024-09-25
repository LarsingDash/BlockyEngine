//
// Created by larsv on 23/09/2024.
//

#include "../Component/Component.h"
#include "GameObject.h"

GameObject::GameObject(std::string t, Transform* parent)
		: tag(std::move(t)), transform(new Transform(this, parent)) {}

GameObject::~GameObject() {
	//Delete transform (which will delete child objects)
	delete transform;

	//Delete all components
	for (auto& component: components) {
		delete component;
	}
}

void GameObject::OnUpdate(float delta) {  // NOLINT(*-no-recursion)
	//Cascade update to components
	for (auto& component: components) {
		component->OnUpdate(delta);
	}

	//Cascade update to child objects
	for (auto& child: transform->getChildren()) {
		child->gameObject->OnUpdate(delta);
	}
}
