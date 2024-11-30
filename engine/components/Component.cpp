//
// Created by larsv on 12/11/2024.
//

#include "gameObject/GameObject.hpp"
#include "Component.hpp"

Component::Component(GameObject& gameObject, const char* tag, bool hasTransform) :
		gameObject{gameObject}, tag{tag},
		componentTransform(hasTransform ? std::make_unique<ComponentTransform>(gameObject, *this) : nullptr) {}

Component::~Component() = default;
