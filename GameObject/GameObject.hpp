//
// Created by larsv on 23/09/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_HPP
#define BLOCKYENGINE_GAMEOBJECT_HPP

#include <string>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "Transform.hpp"
#include "../Component/Component.hpp"

class GameObject {
	public:
		const std::string tag;
		GameObject* parent;

		std::unique_ptr<Transform> transform;

		//----- RULE OF FIVE
		GameObject(std::string t, GameObject* parent);

		explicit GameObject(const std::string& t) : GameObject(t, nullptr) {};
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(const GameObject&& other) = delete;
		GameObject& operator=(const GameObject&& other) = delete;

		//----- CYCLE
		void OnUpdate(float delta);

		//----- CHILD / PARENT
		GameObject& AddChild(const std::string& t);
		bool RemoveChild(GameObject& child);
		void SetParent(GameObject& trans);

		inline std::vector<std::unique_ptr<GameObject>>& GetChildren() { return children; };

		//----- COMPONENTS
		template<typename T, typename... Args>
		T* AddComponent(Args&& ... args) {
			//Perform validity checks
			ComponentValidityCheck<T>();
			
			const auto type = std::type_index(typeid(T));

			//A GameObject may only have one of each type of Component, return if already exists 
			if (components[type] != nullptr) return nullptr;

			//Instantiate new Component of T by perfect forwarding the given arguments, return newly created Component
			components[type] = std::make_unique<T>(*this, *transform, std::forward<Args>(args)...);
			return static_cast<T*>(components[type].get());
		}

		template<typename T>
		void RemoveComponent() {
			//Perform validity checks
			ComponentValidityCheck<T>();

			//Find position of T
			const auto it = components.find(std::type_index(typeid(T)));

			//Remove component if found
			if (it != components.end()) components.erase(it);
		}

		template<typename T>
		T* GetComponent() {
			//Perform Validity Checks
			ComponentValidityCheck<T>(components.begin());

			//Find position of T
			const auto it = components.find(std::type_index(typeid(T)));

			//Return component cast to T if found
			return (it != components.end()) ? static_cast<T*>(it->second.get()) : nullptr;
		}

	private:
		std::vector<std::unique_ptr<GameObject>> children;
		std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

		bool markedForDeletion = false;

		//----- COMPONENTS
		template<typename T>
		inline void ComponentValidityCheck() {
			//Assert that T inherits Component
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		}

		//----- CHILD / PARENT
		void Reparent(GameObject* other);
};

#endif //BLOCKYENGINE_GAMEOBJECT_HPP
