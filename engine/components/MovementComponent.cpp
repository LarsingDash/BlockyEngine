//
// Created by larsv on 22/11/2024.
//

#include "MovementComponent.hpp"

#include <iostream>

#include "gameObject/GameObject.hpp"

MovementComponent::MovementComponent(GameObject& gameObject, const char* tag) :
		Component(gameObject, tag, false) {}

MovementComponent::~MovementComponent() = default;

void MovementComponent::Start() {}

void MovementComponent::Update(float delta) {
//	gameObject.transform->Translate(delta, delta);
//	gameObject.transform->Scale(delta * 100, delta * 100);
//	gameObject.transform->Rotate(1.f);
	gameObject.transform->Rotate(0.025f);
	
//	std::cout << gameObject.tag << ": " << gameObject.transform->GetWorldPosition().x << std::endl;
//	std::cout << gameObject.tag << ": " << gameObject.transform->GetWorldRotation() << std::endl;
//	std::cout << gameObject.tag << ": " << gameObject.transform->GetLocalScale().x << std::endl;
}

void MovementComponent::End() {}
