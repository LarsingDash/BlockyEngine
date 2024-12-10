//
// Created by larsv on 12/11/2024.
//

#include "Component.hpp"

Component::Component(GameObject* gameObject, const char* tag, bool hasTransform) :
		gameObject{gameObject}, tag{tag}, _hasTransform(hasTransform),
		componentTransform(hasTransform ? std::make_unique<ComponentTransform>(*gameObject, this) : nullptr) {}

Component::Component(const Component& other) :
		tag(other.tag), gameObject(other.gameObject), _hasTransform(other._hasTransform),
		componentTransform(other._hasTransform
						   ? std::make_unique<ComponentTransform>(*other.componentTransform)
						   : nullptr) {}

Component* Component::CloneInternal(GameObject& parent) {
	Component* clone = _clone(parent);

	clone->gameObject = &parent;
	if (_hasTransform) {
		clone->componentTransform->component = clone;
		clone->componentTransform->SetParent(*parent.transform);
		clone->componentTransform->SetGameObject(parent);
	}
	
	return clone;
}
