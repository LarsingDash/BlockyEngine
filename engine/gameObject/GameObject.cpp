//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"

GameObject::GameObject(const char* tag) :
		tag{tag}, transform{std::make_unique<Transform>()} {
}

GameObject::~GameObject() {
	for (auto& type : components) {
		for (auto& component : type.second) {
			component->End();
		}
	}
}

void GameObject::Update(float delta) {
	//Cascade update to components
	for (auto& type : components) {
		for (auto& component : type.second) {
			component->Update(delta);
		}
	}
}
