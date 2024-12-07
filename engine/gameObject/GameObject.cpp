﻿//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"

#include "logging/BLogger.hpp"

GameObject::GameObject(std::string tag, GameObject* parent) :
		tag(std::move(tag)), parent(parent), _isMarkedForDeletion(false) {
	transform = std::make_unique<GameObjectTransform>(*this);
}

GameObject::~GameObject() {
	//Mark this for deletion so its children don't try to erase themselves from this children list (on children.clear())
	_isMarkedForDeletion = true;

	//Reparent this to null, removing it from its parents children list
	_reparent(nullptr);

	//Delete all components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			//Call end before deleting
			component->End();
		}
	}
	_components.clear();

	//Delete all child gameObjects
	_children.clear();
}

void GameObject::Update(    // NOLINT(*-no-recursion)
		float delta, std::vector<std::reference_wrapper<Transform>>& recalculationList) {
	//Prevent from being updated if some other object marked this one for deletion
	if (_isMarkedForDeletion) {
		_reparent(nullptr);
		return;
	}

	//Cascade update to components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			component->Update(delta);

			//Break update cycle if one of the components marked this object for deletion
			//Suppressing warnings because CLion can't understand that components can set _isMarkedForDeletion
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "UnreachableCode"
			if (_isMarkedForDeletion) {
				_reparent(nullptr);
				return;
			}
#pragma clang diagnostic pop
		}
	}

	//Add transform to the recalculation list before updating children so that the order will be top to bottom
	if (transform->isMarkedForRecalculation) recalculationList.emplace_back(*transform);
	else    //If not, search through components and add any that are marked
		for (const auto& [key, list] : _components) {
			for (const auto& component : list) {
				if (component->componentTransform != nullptr &&
						component->componentTransform->isMarkedForRecalculation)
					recalculationList.emplace_back(*transform);
			}
		}

	//Cascade update to child objects
	for (auto& child : _children) {
		child->Update(delta, recalculationList);
	}
}

GameObject* GameObject::GetChild(const std::string& t) {
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });

	return (it != _children.end()) ? (*it).get() : nullptr;
}

bool GameObject::RemoveChild(GameObject& child) {
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (&child == cur.get());
						   });

	return _removeChild(it);
}

bool GameObject::RemoveChild(const std::string& t) {
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });

	return _removeChild(it);
}

bool GameObject::_removeChild(std::vector<std::unique_ptr<GameObject>>::iterator it) {
	if (it == _children.end()) return false;

	_children.erase(it);
	return true;
}

void GameObject::Reparent(GameObject& target) {
	//Make sure the target isn't already the parent
	if (&target != parent) {
		//Loop through parent lineage of target to see if 'this' exists
		GameObject* cur = &target;
		bool foundItself = false;
		while (cur) {
			if (cur == this) foundItself = true;
			cur = cur->parent;
		}

		//Reparent if 'this' wasn't found in its parent lineage, otherwise this will create an infinite loop
		if (!foundItself) {
			_reparent(&target);
			transform->RecalculateWorldMatrix();
		}
	}
}

void GameObject::Destroy() { _isMarkedForDeletion = true; }

void GameObject::_reparent(GameObject* target) {
	//Check if a parent is present (to prevent reparenting the root and the practice of creating a GameObject without AddChild()) 
	//Also check if the parent isn't marked for deletion, reparenting if this is so will pointlessly call the destructor again
	if (!parent || parent->_isMarkedForDeletion) return;

	//Find itself in the given GameObject's children list
	auto& parentChildren = parent->_children;
	auto begin = parentChildren.begin();
	auto end = parentChildren.end();

	auto selfPosition = std::find_if(begin, end,
									 [&](const std::unique_ptr<GameObject>& cur) {
										 return cur.get() == this;
									 });

	//If itself has been found in the parent, reparent itself to the target
	if (selfPosition != end) {
		try {
			//Move itself to new parents children list
			//Skipping this step when the target is nullptr effectively means 'this' cleanly destructs itself
			if (target) target->_children.push_back(std::move(*selfPosition));

			//Erase from previous parents children list (will destruct itself if previous was skipped
			parentChildren.erase(selfPosition);

			//Rebind parent pointer on self and transform unless destroyed
			if (target) {
				parent = target;
				transform->SetParent(*target->transform);
			}
		} catch (const std::exception& e) {
			std::string err = "Exception occurred while reparenting: ";
			err += e.what();
			BLOCKY_ENGINE_ERROR(err)
		}
	}
}
