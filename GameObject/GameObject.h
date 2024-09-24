//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_H
#define BLOCKYENGINE_GAMEOBJECT_H

//Forward declaration to resolve circular dependence
class Component;

#include <string>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "../Component/Transform.h"

class GameObject {
	public:
		const std::string tag;
		Transform* transform;

		GameObject(std::string t, Transform* parent);
		~GameObject();

		void OnUpdate(float delta);

		template<typename T, typename... Args>
		T* AddComponent(Args&& ... args) {
			//Assert that T inherits Component
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

			//Initialise T, args will be matched with a constructor on compile time (and while CLion is indexing) 
			T* component = new T(this, transform, std::forward<Args>(args)...);

			//Check if this GameObject already has a component of type T
			if (components.find(typeid(T)) == components.end()) {   //First of T
				//Make new list with it
				std::vector<Component*> list;
				list.push_back(component);
				components[typeid(T)] = static_cast<const std::vector<Component*>>(list);
			} else {    //GameObject already as T
				//Add to the list
				components[typeid(T)].push_back(component);
			}

			return component;
		}

		//TODO Remove components
	private:
		std::unordered_map<std::type_index, std::vector<Component*>> components;
};

#endif //BLOCKYENGINE_GAMEOBJECT_H
