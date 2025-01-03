﻿//
// Created by larsv on 12/11/2024.
//

#include "GameObject.hpp"

#include "logging/BLogger.hpp"

GameObject::GameObject(std::string tag, GameObject* parent) :
		tag(std::move(tag)), parent(parent), _isMarkedForDeletion(false), isActive(true), _deletionList() {
	transform = std::make_unique<GameObjectTransform>(*this);
}

GameObject::~GameObject() {
	//Mark this for deletion so its children don't try to erase themselves from this children list (on children.clear())
	_isMarkedForDeletion = true;

	//Delete all components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			//Call end before deleting
			if (isActive) {
				component->End();
			}
		}
	}
	_components.clear();

	//Delete all child gameObjects
	_children.clear();
}

GameObject::GameObject(const GameObject& other) :
		tag(other.tag), parent(other.parent), transform(std::make_unique<GameObjectTransform>(*other.transform)), isActive(other.isActive),
		_isMarkedForDeletion(other._isMarkedForDeletion), _deletionList(other._deletionList) {
	transform->SetGameObject(*this);

	for (const auto& type : other._components) {
		for (const auto& comp : type.second) {
			_components[type.first].emplace_back(
					std::unique_ptr<Component>(comp->CloneInternal(*this))
			);
		}
	}

	_children.reserve(other._children.size());
	for (const auto& child : other._children) {
		auto& created = _children.emplace_back(std::make_unique<GameObject>(*child));
		created->parent = this;
		created->transform->SetParent(*transform);
	}
}

void GameObject::Update(    // NOLINT(*-no-recursion)
		float delta, std::vector<std::reference_wrapper<Transform>>& recalculationList) {
	//Cancel update cycle if it was marked before by something else or is inactive
	if (!isActive || _isMarkedForDeletion) return;
	
	//Cascade update to components
	for (auto& type : _components) {
		for (auto& component : type.second) {
			component->Update(delta);

			//Break update cycle if one of the components marked this object for deletion
			//Suppressing warnings because CLion can't understand that components can set _isMarkedForDeletion
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "UnreachableCode"
			if (_isMarkedForDeletion) return;
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
	for (size_t i = 0; i < _children.size(); ++i) { // NOLINT(*-loop-convert)
		auto& child = _children[i];
		//Prevent from being updated if some other object marked this one for deletion
		if (!child->_isMarkedForDeletion) {
			child->Update(delta, recalculationList);
			
			//Check if child marked this object for deletion, otherwise check if child is marked (since deleting this will delete child anyway_
			//Suppressing warnings because CLion can't understand that children can set their parent's _isMarkedForDeletion
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#pragma ide diagnostic ignored "UnreachableCode"
			if (_isMarkedForDeletion) return;
#pragma clang diagnostic pop
			else {
				//Get child again from the _children vector, in case a sibling has been added that exceeded the capacity
				//(This would've moved the current 'child' to a different location)
				auto& updatedChild = _children[i];
				if (updatedChild->_isMarkedForDeletion) {
					_deletionList.emplace_back(updatedChild.get());
				}
			}
		}
	}

	if (!_deletionList.empty()) {
		for (auto child : _deletionList) {
			child->_reparent(nullptr);
		}
		_deletionList.clear();
	}
}

void GameObject::SetActive(bool active, bool force) {    // NOLINT(*-no-recursion)
	//Early return if nothing changed
	if (isActive == active && !force) return;
	isActive = active;

	//Cascade End to components
	if (isActive) {
		transform->RecalculateWorldMatrix();

		for (auto& type : _components) {
			for (auto& component : type.second) {
				component->Start();
			}
		}
	} else {
		for (auto& type : _components) {
			for (auto& component : type.second) {
				component->End();
			}
		}
	}

	for (auto& child : _children) {
		child->SetActive(isActive, force);
	}
}

GameObject& GameObject::AddChild(std::string_view childTag) {
	//Instantiate new GameObject in this children list
	GameObject& child = *_children.emplace_back(
			std::make_unique<GameObject>(std::forward<std::string>(childTag.data()), this)
	);

	//Pass active mode onto child
	child.SetActive(isActive, true);

	//Return newly created child
	return child;
}

GameObject& GameObject::AddChild(GameObject& prefab) {
	//Instantiate new GameObject in this children list
	GameObject& child = *_children.emplace_back(std::make_unique<GameObject>(prefab));

	//Pass active mode onto child
	child.SetActive(isActive, true);

	//Return newly created child
	return child;
}

GameObject* GameObject::GetChild(const std::string& t, bool recursive) {    // NOLINT(*-no-recursion)
	auto it = std::find_if(_children.begin(), _children.end(),
						   [&](std::unique_ptr<GameObject>& cur) {
							   return (t == cur->tag);
						   });

	if (it != _children.end()) return (*it).get();
	else if (recursive) {
		for (auto& child : _children) {
			GameObject* result = child->GetChild(t, recursive);
			if (result) return result;
		}
	} 
	
	return nullptr;
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

void GameObject::SetParent(GameObject& target) {
	parent = &target;
	transform->SetParent(*target.transform);
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
				transform->SetParent(*(target->transform));
			}
		} catch (const std::exception& e) {
			std::string err = "Exception occurred while reparenting: ";
			err += e.what();
			BLOCKY_ENGINE_ERROR(err);
		}
	}
}
