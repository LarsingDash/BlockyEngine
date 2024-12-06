//
// Created by larsv on 03/12/2024.
//

#include "RotationComp.hpp"

#include "gameObject/GameObject.hpp"

RotationComp::RotationComp(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false) {}

RotationComp::~RotationComp() = default;

Component* RotationComp::_cloneImpl(GameObject& parent) {
	auto clone = new RotationComp(*this);
	return clone;
}

void RotationComp::Start() {}

void RotationComp::Update(float delta) {
	gameObject->transform->Rotate(delta * 75.f);
	
	float cur = gameObject->transform->GetLocalRotation();
	if (cur > 360.f) gameObject->transform->SetRotation(cur - 360.f);
	if (cur < -360.f) gameObject->transform->SetRotation(cur + 360.f);
}

void RotationComp::End() {}
