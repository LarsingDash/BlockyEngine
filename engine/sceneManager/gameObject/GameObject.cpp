//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(const char* tag) :
		tag{tag}, transform{std::make_unique<Transform>()} {
}

void GameObject::Update(float delta) {
	//Cascade update to components
	for (auto& type: components) {
		for (auto& component: type.second) {
			component->Update(delta);
		}
	}
}
