//
// Created by larsv on 29/11/2024.
//

#include "MovementComp.hpp"

#include "gameObject/GameObject.hpp"
#include "glm/trigonometric.hpp"

MovementComp::MovementComp(GameObject* gameObject, const char* tag) :
		Component(gameObject, tag, false), _direction(1, 0), _speed(15.f) {}

MovementComp::~MovementComp() = default;

Component* MovementComp::_cloneImpl(GameObject& parent) {
	auto clone = new MovementComp(*this);
	return clone;
}

void MovementComp::Start() {}

void MovementComp::Update(float delta) {
	gameObject->transform->Translate(_direction.x * delta * _speed, _direction.y * delta * _speed);

	if (glm::length(gameObject->transform->GetLocalPosition()) > 7.f) {
		gameObject->Destroy();
	}
}

void MovementComp::End() {}

void MovementComp::SetDirectionByAngle(float angle) {
	float radians = glm::radians(angle);

	_direction.x = std::cos(radians);
	_direction.y = std::sin(radians);
}
