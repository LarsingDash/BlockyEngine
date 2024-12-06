//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_COMPONENT_HPP
#define BLOCKYENGINE_COMPONENT_HPP

#include <memory>
#include <string>

#include "ComponentTransform.hpp"

class GameObject;

class Component {
	public:
		Component(GameObject* gameObject, const char* tag, bool hasTransform = true);
		virtual ~Component();

		Component(const Component& other);
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(Component&& other) noexcept = delete;
		
		Component* CloneInternal(GameObject& parent);

		virtual void Start() = 0;
		virtual void Update(float delta) = 0;
		virtual void End() = 0;

		std::string tag;
		GameObject* gameObject;
		std::unique_ptr<ComponentTransform> componentTransform;
		
	private:
		virtual Component* _clone(const GameObject& parent) = 0;
		bool _hasTransform;
};

#endif //BLOCKYENGINE_COMPONENT_HPP
