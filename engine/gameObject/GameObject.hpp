//
// Created by larsv on 12/11/2024.
//

#ifndef BLOCKYENGINE_GAMEOBJECT_HPP
#define BLOCKYENGINE_GAMEOBJECT_HPP

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <optional>

#include "Transform.hpp"
#include "components/Component.hpp"

class GameObject {
	public:
		//----- RULE OF FIVE
		explicit GameObject(const char* tag);
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(const GameObject&& other) = delete;
		GameObject& operator=(const GameObject&& other) = delete;

		//----- CYCLE
		void Update(float delta);

		//----- COMPONENTS
		template<typename T, typename... Args>
		T& AddComponent(const char* componentTag = "Untagged", Args&& ... args) {
			//Perform validity checks
			ComponentValidityCheck<T>();
			const auto type = std::type_index(typeid(T));

			//Create component and call Start() on it
			auto typeIt = components.find(type);
			std::unique_ptr<T> component = std::make_unique<T>(*this, componentTag, std::forward<Args>(args)...);
			component->Start();

			//Find component list, create it if there was none
			if (typeIt == components.end()) {
				//Create new list with the 
				auto& typeList = components[type];
				return static_cast<T&>(*typeList.emplace_back(std::move(component)));
			} else {
				//Add new component to existing list
				return static_cast<T&>(*typeIt->second.emplace_back(std::move(component)));
			}
		}

		template<typename T>
		void RemoveComponent(const std::string& componentTag = "") {
			std::optional<ComponentsList::iterator> componentIt = findComponentByTag<T>(componentTag);

			if (componentIt) {
				//Call End()
				(*componentIt.value())->End();

				//Erase
				auto& typeList = components[typeid(T)];
				typeList.erase(*componentIt);

				//Remove list if it's empty
				if (typeList.empty()) {
					components.erase(typeid(T));
				}
			}
		}

		template<typename T>
		T* GetComponent(const std::string& componentTag = "") {
			auto componentIt = findComponentByTag<T>(componentTag);

			//Return tagged component cast to T* if found
			return componentIt ? static_cast<T*>((**componentIt).get()) : nullptr;
		}

		const std::string tag;

		std::unique_ptr<Transform> transform;

	private:
		//----- COMPONENTS
		template<typename T>
		inline void ComponentValidityCheck() {
			//Assert that T inherits Component
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		}

		using ComponentsList = std::vector<std::unique_ptr<Component>>;
		//Finds an iterator to the component with the templated tag and given tag
		//If the component was found, the given pointer will be set to it
		template<typename T>
		std::optional<ComponentsList::iterator> findComponentByTag(const std::string& componentTag) {
			//Perform Validity Checks
			ComponentValidityCheck<T>();

			//Find position of T and return nullptr if it wasn't found or the list was empty
			const auto typeIt = components.find(std::type_index(typeid(T)));
			if (typeIt == components.end() || typeIt->second.empty()) return std::nullopt;

			//If no tag was given: return first component cast to T*
			if (componentTag.empty()) {
				return std::optional{typeIt->second.begin()};
			}

			//Search for specific component by the given tag
			auto& typeList = typeIt->second;
			const auto componentIt = std::find_if(typeList.begin(), typeList.end(),
												  [&componentTag](const std::unique_ptr<Component>& comp) {
													  return comp->tag == componentTag;
												  });

			return (componentIt != typeList.end()) ? std::optional{componentIt} : std::nullopt;
		}

		std::unordered_map<std::type_index, ComponentsList> components;
};

#endif //BLOCKYENGINE_GAMEOBJECT_HPP