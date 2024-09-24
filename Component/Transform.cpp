//
// Created by larsv on 23/09/2024.
//

#include "Transform.h"
#include "../GameObject/GameObject.h"

Transform::Transform(GameObject* gameObject, Transform* parent) : gameObject(gameObject), parent(parent),
																  position(), rotation(), scale() {
	if (parent) parent->children.push_back(this);
}

Transform::~Transform() {
	if (parent) {
		removeChild(parent);
	}

	for (auto child: children) {
		delete child->gameObject;
	}
}

void Transform::removeChild(Transform* transform) {
	auto it = std::find(transform->children.begin(), transform->children.end(), this);
	if (it != transform->children.end()) {
		transform->children.erase(it);
	}
}

void Transform::setParent(Transform* transform) {
	if (transform != parent) {
		removeChild(parent);
		
		parent = transform;
		if (parent) parent->children.push_back(this);
	}
}