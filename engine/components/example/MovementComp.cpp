//
// Created by larsv on 29/11/2024.
//

#include "MovementComp.hpp"

#include "gameObject/GameObject.hpp"

MovementComp::MovementComp(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false) {}

MovementComp::~MovementComp() = default;

Component* MovementComp::_cloneImpl(GameObject& parent) {
	auto clone = new MovementComp(*this);
	return clone;
}

void MovementComp::Start() {}

void MovementComp::Update(float delta) {
	gameObject->transform->Translate(delta * 25.f, 0.f);

	if (gameObject->transform->GetLocalPosition().x > 12.5f) {
		gameObject->Destroy();
	}
}

void MovementComp::End() {}