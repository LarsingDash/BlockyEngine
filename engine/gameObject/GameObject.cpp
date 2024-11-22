//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"

GameObject::GameObject(std::string tag, GameObject* parent) :
		tag(std::move(tag)), parent(parent) {
	transform = std::make_unique<Transform>(*this);
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
	_children.clear();
}

void GameObject::Update(    // NOLINT(*-no-recursion)
		float delta, std::vector<std::reference_wrapper<Transform>>& recalculationList) {
	//Cascade update to components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			component->Update(delta);
		}
	}
	if (tag == "root" || tag == "A") transform->Translate(0.1f, 0.f);

	//Add transform to the recalculation list before updating children so that the order will be top to bottom
	if (transform->isMarkedForRecalculation) recalculationList.emplace_back(*transform);

	//Cascade update to child objects
	for (auto& child : _children) {
		child->Update(delta, recalculationList);
	}
}

GameObject* GameObject::GetChild(const std::string& t) {
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });

	return (it != _children.end()) ? (*it).get() : nullptr;
}

bool GameObject::RemoveChild(GameObject& child) {
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (&child == cur.get());
						   });

	return _removeChild(it);
}

bool GameObject::RemoveChild(const std::string& t) {
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });

	return _removeChild(it);
}

bool GameObject::_removeChild(std::vector<std::unique_ptr<GameObject>>::iterator it) {
	if (it == _children.end()) return false;

	_children.erase(it);
	return true;
}
