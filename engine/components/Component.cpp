//
// Created by larsv on 12/11/2024.
//

#include "gameObject/GameObject.hpp"
#include "Component.hpp"

Component::Component(GameObject* gameObject, const char* tag, bool hasTransform) :
		gameObject{gameObject}, tag{tag},
		componentTransform(hasTransform ? std::make_unique<ComponentTransform>(*gameObject, this) : nullptr) {}

Component::~Component() = default;

Component::Component(const Component& other) :
		tag(other.tag), gameObject(other.gameObject),
		componentTransform(std::make_unique<ComponentTransform>(*other.componentTransform)) {}
		
void Component::Reparent(GameObject* parent) {
	gameObject = parent;
	componentTransform->component = this;
	componentTransform->SetParent(*gameObject->transform);
}
