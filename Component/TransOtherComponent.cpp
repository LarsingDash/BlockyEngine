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
	if (gameObject.tag == "Child1")	transform.SetLocalPosition(cur.x + 1.f * delta, cur.y + 0.5f * delta);
	transform.SetLocalRotation(transform.GetLocalRotation() + glm::radians(360.f / 2.5f * delta));
	if (gameObject.tag == "Child1")	transform.SetLocalScale(transform.GetLocalScale() + 0.05f * delta);
}
