//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_HPP
#define BLOCKYENGINE_COMPONENT_HPP

class GameObject;
class Transform;

class Component {
	public:
		GameObject& gameObject;
		Transform& transform;

		Component(GameObject& gameObject, Transform& transform)
				: gameObject(gameObject), transform(transform) {}

		virtual void OnUpdate(float delta) = 0;
		virtual ~Component() = default;
};


#endif //BLOCKYENGINE_COMPONENT_HPP
