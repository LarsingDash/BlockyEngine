//
// Created by larsv on 23/09/2024.
//

#include "Transform.h"
#include "GameObject.h"

Transform::Transform(GameObject* gameObject, Transform* parent) : gameObject(gameObject), parent(parent),
																  position(), rotation(), scale() {
	if (parent) parent->children.push_back(this);
}

Transform::~Transform() {
	if (parent) {
		auto it = std::find(parent->children.begin(), parent->children.end(), this);
		if (it != parent->children.end()) {
			parent->children.erase(it);
		}
	}

	for (auto child: children) {
		delete child->gameObject;
	}
}