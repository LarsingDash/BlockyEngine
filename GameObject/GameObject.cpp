//
// Created by larsv on 23/09/2024.
//

#include "GameObject.h"

GameObject::~GameObject() {
	delete transform;
	std::cout << "removing " << tag << std::endl;

	for (auto& pair: components) {
		delete pair.second;
	}
}

//TODO make sure no gameObject can ever be it's own child
void GameObject::OnUpdate(float delta) {  // NOLINT(*-no-recursion)
	for (auto& pair: components) {
		pair.second->OnUpdate(delta);
	}

	for (auto& child : transform->getChildren()) {
		child->gameObject->OnUpdate(delta);
	}
}
