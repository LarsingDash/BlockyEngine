//
// Created by larsv on 23/09/2024.
//

#include "Transform.h"
#include "../GameObject/GameObject.h"

Transform::Transform(GameObject* gameObject, Transform* parent) : gameObject(gameObject), parent(parent),
																  position(), rotation(), scale() {
	//Add this to assigned parent's child list
	if (parent) parent->children.push_back(this);
}

Transform::~Transform() {
	//If there is a parent (not the root), remove this from its child list
	if (parent) {
		removeThisFromTrans(parent);
	}

	//Delete all child objects
	for (auto child: children) {
		delete child->gameObject;
	}
}

void Transform::removeThisFromTrans(Transform* trans) {
	//Find itself in the given transform and remove it
	auto it = std::find(trans->children.begin(), trans->children.end(), this);
	if (it != trans->children.end()) {
		trans->children.erase(it);
	}
}

//TODO prevent parent from being set to nullptr, only root's parent is null (also check in constructor). This is to prevent dangling GameObjects
void Transform::setParent(Transform* transform) {
	//Make sure the new transform isn't already the parent
	if (transform != parent) {
		//Loop through parent lineage of the new parent to see if 'this' exists
		Transform* cur = transform;
		bool foundItself = false;
		while (cur) {
			if (cur == this) foundItself = true;
			cur = cur->parent;
		}

		//Assigning the new parent if 'this' was found in its parent lineage will create infinite loop
		if (!foundItself) {
			//Remove itself from its original parent
			removeThisFromTrans(parent);

			//Assign new parent and add itself to its children
			parent = transform;
			if (parent) parent->children.push_back(this);
		}
	}
}