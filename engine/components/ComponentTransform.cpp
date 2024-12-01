//
// Created by larsv on 13/11/2024.
//

#include "gameObject/GameObject.hpp"

#include "ComponentTransform.hpp"

ComponentTransform::ComponentTransform(GameObject& gameObject, Component& component) :
		Transform(gameObject), component(component) {
	_parent = gameObject.transform.get();
	_recalculateWorldMatrix();
}

void ComponentTransform::RecalculateWorldMatrix() {
	_recalculateWorldMatrix();
}
