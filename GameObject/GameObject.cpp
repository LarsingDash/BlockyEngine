//
// Created by larsv on 23/09/2024.
//

#include "GameObject.h"

GameObject::~GameObject() {
	delete transform;
	std::cout << "removing " << tag << std::endl;

	for (auto& types: components) {
		for (auto& component: types.second) {
			delete component;
		}
	}
}

//TODO make sure no gameObject can ever be it's own child
void GameObject::OnUpdate(float delta) {  // NOLINT(*-no-recursion)
	for (auto& types: components) {
		for (auto& component: types.second) {
			component->OnUpdate(delta);
		}
	}

	for (auto& child: transform->getChildren()) {
		child->gameObject->OnUpdate(delta);
	}
}
