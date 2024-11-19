//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(const char* tag, GameObject* parent) :
		tag(tag), parent(parent), transform(std::make_unique<Transform>()) {
}

GameObject::~GameObject() {
	//Delete all components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			component->End();
		}
	}
	_components.clear();

	//Delete all child gameObjects
	children.clear();
}

void GameObject::Update(float delta) {	// NOLINT(*-no-recursion)
	//Cascade update to components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			component->Update(delta);
		}
	}

	//Cascade update to child objects
	for (auto& child: children) {
		child->Update(delta);
	}
}
