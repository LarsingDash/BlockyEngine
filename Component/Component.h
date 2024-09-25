//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_H
#define BLOCKYENGINE_COMPONENT_H

#include "Transform.h"
#include "../GameObject/GameObject.h"

class Component {
	public:
		GameObject* gameObject;
		Transform* transform;

		Component(GameObject* gameObject, Transform* transform)
				: gameObject(gameObject), transform(transform) {}

		virtual void OnUpdate(float delta) = 0;
		virtual ~Component() = default; //"gameObject->RemoveComponent<DerivedComponent>()" MUST BE CALLED
};


#endif //BLOCKYENGINE_COMPONENT_H
