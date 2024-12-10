//
// Created by larsv on 13/11/2024.
//

#ifndef BLOCKYENGINE_COMPONENTTRANSFORM_HPP
#define BLOCKYENGINE_COMPONENTTRANSFORM_HPP

class Component;

#include "gameObject/Transform.hpp"

class ComponentTransform : public Transform {
	public:
		explicit ComponentTransform(GameObject& gameObject, Component* component);
		void RecalculateWorldMatrix() override;
		
		Component* component;
};

#endif //BLOCKYENGINE_COMPONENTTRANSFORM_HPP