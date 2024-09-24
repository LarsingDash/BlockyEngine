//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_H
#define BLOCKYENGINE_GAMEOBJECT_H

#include <string>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "../Component/Component.h"
#include "../Component/Transform.h"

class GameObject {
	public:
		const std::string tag;
		Transform* transform;

		GameObject(std::string  t, Transform* parent)
				: tag(std::move(t)), transform(new Transform(this, parent)) {}

		~GameObject();
		
		void OnUpdate(float delta);
		
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

			T* component = new T(std::forward<Args>(args)...);
			components[typeid(T)] = component;
			return component;
		}
	private:
		std::unordered_map<std::type_index, Component*> components;
};

#endif //BLOCKYENGINE_GAMEOBJECT_H
