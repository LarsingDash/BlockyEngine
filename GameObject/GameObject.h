//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_H
#define BLOCKYENGINE_GAMEOBJECT_H

//Forward declaration to resolve circular dependence
class Component;

class ExampleComponent;

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
			//Perform validity checks
			if (GetComponent<T>() == nullptr) {
				//Initialise T, args will be matched with a constructor on compile time (and while CLion is indexing) 
				T* component = new T(this, transform, std::forward<Args>(args)...);

				//Push new component on the list of components
				components.push_back(component);

				//Return newly created component
				return component;
			} else return nullptr;
		}

		template<typename T>
		void RemoveComponent() {
			//Perform validity checks
			ComponentValidityCheck<T>();

			//Find component to remove
			auto found = std::remove_if(components.begin(), components.end(), [&](const auto& component) {
				return dynamic_cast<T*>(component) != nullptr;
			});

			//Erase component if found was found
			if (found != components.end()) {
				components.erase(found, components.end());
			}
		}

		template<typename T>
		T* GetComponent() {
			ComponentValidityCheck<T>();

			//Test for duplicates, only one component of each type may be present
			auto result = std::find_if(components.begin(), components.end(), [&](const auto& component) {
				return dynamic_cast<T*>(component) != nullptr;
			});
			
			//Return component if it was found
			return (result != components.end()) ? dynamic_cast<T*>(*result) : nullptr;
		}

	private:
		std::vector<Component*> components;

		template<typename T>
		void ComponentValidityCheck(){
			//Assert that T inherits Component
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		}
};

#endif //BLOCKYENGINE_GAMEOBJECT_H
