//
// Created by larsv on 23/09/2024.
//

#include "../Component/Component.h"
#include "GameObject.h"

#include <utility>

GameObject::GameObject(std::string t, GameObject* parent)
		: tag(std::move(t)), parent(parent), transform(std::make_unique<Transform>(*this)) {
}

GameObject::~GameObject() {
	//Mark this for deletion so its children don't try to erase themselves from this children list (on children.clear())
	markedForDeletion = true;
	std::cout << "Deleting " << tag << std::endl;

	//Reparent this to null, removing it from its parents children list
	Reparent(nullptr);

	//Delete all child gameObjects
	children.clear();

	//Delete all components
	for (auto& component: components) {
		delete component;
	}
}

void GameObject::OnUpdate(float delta) {  // NOLINT(*-no-recursion)
	//Cascade update to components
	for (auto& component: components) {
		component->OnUpdate(delta);
	}

	//Cascade update to child objects
	for (auto& child: children) {
		child->OnUpdate(delta);
	}
}

GameObject& GameObject::AddChild(const std::string& t) {
	//Instantiate new GameObject in this children list
	children.push_back(std::make_unique<GameObject>(t, this));

	//Return newly created child
	return *children.back();
}

void GameObject::SetParent(GameObject& target) {
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
		if (!foundItself) Reparent(&target);
	}
}

void GameObject::Reparent(GameObject* other) {
	//Check if a parent is present (to prevent reparenting the root and the practice of creating a GameObject without addChild()) 
	//Also check if the parent isn't marked for deletion, reparenting if this is so will pointlessly call the destructor again
	if (!parent || parent->markedForDeletion) return;

	//Find itself in the given transform and remove selfPosition
	auto& parentChildren = parent->children;
	auto begin = parentChildren.begin();
	auto end = parentChildren.end();

	auto selfPosition = std::find_if(begin, end,
									 [&](const std::unique_ptr<GameObject>& cur) {
										 return cur.get() == this;
									 });

	//If this exists in parent children list:
	if (selfPosition != end) {
		parent = other;	//Reparent
		if (other) other->children.push_back(std::move(*selfPosition));	//Move itself to new parents children list (unless reparenting to null)
		parentChildren.erase(selfPosition);	//Erase from previous parents children list
	}
}