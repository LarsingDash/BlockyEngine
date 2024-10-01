//
// Created by larsv on 01/10/2024.
//

#include "TransOtherComponent.hpp"
#include "../renderer.cpp"
#include "trigonometric.hpp"

TransOtherComponent::TransOtherComponent(GameObject& gameObject, Transform& transform)
		: Component(gameObject, transform) {}

void TransOtherComponent::OnUpdate(float delta) {
	const glm::vec2& cur = transform.GetLocalPosition();
	transform.SetLocalPosition(cur.x + 40.f * delta, cur.y + 20.f * delta);
	transform.SetLocalRotation(transform.GetLocalRotation() + glm::radians(360.f / 5.f * delta));
	transform.SetLocalScale(transform.GetLocalScale() + 5.0f * delta);
}

