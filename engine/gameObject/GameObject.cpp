//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(std::string tag, GameObject* parent) :
		tag(std::move(tag)), parent(parent), transform(std::make_unique<Transform>()) {
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

GameObject* GameObject::GetChild(const std::string& t) {
	auto it = std::find_if(children.begin(), children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });
	
	return (it != children.end()) ? (*it).get() : nullptr;
}

bool GameObject::RemoveChild(GameObject& child) {
	auto it = std::find_if(children.begin(), children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (&child == cur.get());
						   });

	return _removeChild(it);
}

bool GameObject::RemoveChild(const std::string& t) {
	auto it = std::find_if(children.begin(), children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });

	return _removeChild(it);
}

bool GameObject::_removeChild(std::vector<std::unique_ptr<GameObject>>::iterator it) {
	if (it == children.end()) return false;

	children.erase(it);
	return true;
}
